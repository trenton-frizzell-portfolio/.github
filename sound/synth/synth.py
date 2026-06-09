import argparse
import numpy as np
import sounddevice as sd
from scipy import signal
import rtmidi
import mido

fs = 48000
f = 440
amplitude = 0.708
start_index = 0
port = mido.open_input('IAC Driver Bus 1')
velocity_scale = 0

parser = argparse.ArgumentParser()
parser.add_argument("-w", "--wave", default="saw", choices=["saw", "sine", "square", "triangle"])
args = parser.parse_args()

class Envelope:
    def __init__(self):
        self.stage = "off"
        self.level = 0.0
        self.ramp = 480
        self.step = 1.0 / self.ramp
    
    def note_on(self):
        # triggered by KEY ON - begin attack
        self.stage = "attack"
    
    def note_off(self):
        # triggered by KEY OFF - begin release
        self.stage = "release"

    def next_block(self, frames):
        out = np.empty(frames)
        for i in range(frames):
            if self.stage =="attack":
                self.level += self.step     # step = 1.0/480
                if self.level >= 1.0:
                    self.level = 1.0
                    self.stage = "sustain"
            elif self.stage == "sustain":
                self.level = 1.0
            elif self.stage == "release":
                self.level -= self.step
                if self.level <= 0.0:
                    self.level = 0.0
                    self.stage = "off"
            elif self.stage == "off":
                self.level = 0.0
            out[i] = self.level
        return out

envelope = Envelope()

def midi_handler():
    global f, velocity_scale

    for msg in port.iter_pending():
        
        # check to see if theres a message
        if msg.type == 'note_on' and msg.velocity > 0:
            # trying to adjust for velocity but keyboard strokes dont recognize velocity I think
            velocity_scale = (msg.velocity/127)**2
            f = 440 * 2**((msg.note - 69) / 12)
            envelope.note_on()
            
        elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
            # when KEY OFF arrives
            envelope.note_off()
            


def callback(outdata, frames, time, status):
    global start_index, velocity_scale
    # midi_note = input from midi device
    env_block = envelope.next_block(frames).reshape(-1, 1)

    if status:
        print(status)
    t = (start_index + np.arange(frames)) / fs
    t = t.reshape(-1, 1)

    # parse args to get wave form
    if args.wave == "saw":
        wave = signal.sawtooth(2 * np.pi * f * t)
    elif args.wave == "sine":
        wave = np.sin(2 * np.pi * f * t)
    elif args.wave == "square":
        wave = signal.square(2 * np.pi * f * t)
    elif args.wave == "triangle":
        wave = signal.sawtooth(2 * np.pi * f * t, width=0.5)
 
    outdata[:] = amplitude * velocity_scale * env_block * wave
    start_index += frames

def main():
    global f
    with sd.OutputStream(channels=1, samplerate=fs, callback=callback):
        while True:
            midi_handler()
            sd.sleep(1)

if __name__ == "__main__":
        main()
