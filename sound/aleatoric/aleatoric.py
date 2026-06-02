import argparse
import numpy as np
from scipy.io.wavfile import write
from scipy import signal
import sounddevice as sd
import random
#import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument("-o", "--output", help="Output as a .wav file")
parser.add_argument("-b", "--bass", action="store_true", help="For each measure, play the chord root as a whole note two octaves lower.")
parser.add_argument("-a", "--harmony", action="store_true", help="For each melody note, also play the closest chord note below.")
parser.add_argument("-r", "--rhythm", action="store_true", help="(UNDER CONSTRUCTION) Instead of eighth notes, pick a random note pattern for the verse, and another for the chorus.")
parser.add_argument("-d", "--drums", action="store_true", help="(UNDER CONSTRUCTION) Add a drum track using white noise.")
parser.add_argument("-m", "--midi", action="store_true", help="(UNDER CONSTRUCTION) Make the program act as a MIDI controller rather than playing sounds itself.")
parser.add_argument("-v", "--verbose", action="store_true", help="Make the operation more talkative")
args = parser.parse_args()

if args.verbose:
    print("Verbose enabled")


chord_progressions = [['I', 'IV', 'ii', 'V'], 
                      ['I', 'vi', 'ii', 'V'], 
                      ['I', 'iii', 'IV', 'iv'], 
                      ['I', 'V', 'ii', 'V'], 
                      ['I', 'vi', 'IV', 'V'], 
                      ['IV', 'I', 'vi', 'IV'], 
                      ['I', 'V', 'vi', 'I'], 
                      ['I', 'IV', 'iv', 'I'], 
                      ['IV', 'V', 'I', 'I'], 
                      ['vi', 'IV', 'I', 'V']]
random.shuffle(chord_progressions)
song_form = [['A', 'A', 'B', 'B', 'C', 'C'], 
             ['A', 'B', 'A', 'B', 'C', 'D'], 
             ['A', 'B', 'C', 'D', 'D', 'D']]
scale_degrees = {"I": 0, "ii": 2, "iii": 4, "IV": 5, "iv": 5, "V": 7, "vi": 9}

# randomly pick one of the following song structures: "AABB/CC", "ABAB/CD", "AB/CDDD"
def get_song_form():
    return random.choice(song_form)

# choose randomly one of the following chord_progressions
def get_chord_progression(): 
    return chord_progressions.pop(0)

# Pick a random key (base scale note) in the range A3-A4 inclusive
def get_key():
    # get random form range midi A3(57) to midi A4(69)
    return random.randint(57, 69)

# Pick a tempo between 80 and 160 beats per minute. The song will be in "common time" 
def get_tempo():
    #generate random tempo 80 - 160
    return random.randint(80, 160)

# Pick a note from the current chord with probability 0.8, 
# else another note from the major scale. 
# All notes should be in the first octave of the song's key (major scale).
def get_melody(form, song_progression, key):
    melody = []

    # generates major scale as MIDI numbers offset from the key
    scale = [key + interval for interval in [0, 2, 4, 5, 7, 9, 11]]

    # iterate through each line of the song form i.e. AABBCC
    for letter in form:
        # iterate through the 4 chords of this progression i.e. I-IV-ii-V 
        for chord in song_progression[letter]:                
            # the chord's root note in MIDI (key + scale degree offset)
            chord_root = key + scale_degrees[chord]
            # minor chord (lowercase numeral) uses a minor third (+3)
            if chord.islower():
                third = chord_root + 3
            # major chord (uppercase numeral) uses a major third (+4)
            else:
                third = chord_root + 4
            fifth = chord_root + 7
            chord_tones = [chord_root, third, fifth]

            for eighth_note in range(8):

                # 80% chance: pick a note from the current chord
                if random.random() <= 0.8:
                    eighth_note = random.choice(chord_tones)
                    melody.append(eighth_note)
                # 20% chance: pick any note from the major scale
                else:
                    eighth_note = random.choice(scale)
                    melody.append(eighth_note)

    return melody



# For each measure, play the chord root as a whole note two octaves lower.
def get_bass_line(form, song_progression, key):
    bass_line = []

    # iterate through each line of the song form i.e. AABBCC
    for letter in form:
        # iterate through the 4 chords of this progression i.e. I-IV-ii-V 
        for chord in song_progression[letter]:
            for eighth_note in range(8):
                # the chord's root note in MIDI (key + scale degree offset)
                eighth_note = (key + scale_degrees[chord]) - 24
                bass_line.append(eighth_note)
    return bass_line

def get_harmony(form, song_progression, key, melody):
    i = 0
    harmony = []
    
    # iterate through each line of the song form i.e. AABBCC
    for letter in form:
        # iterate through the 4 chords of this progression i.e. I-IV-ii-V 
        for chord in song_progression[letter]:                
            root = key + scale_degrees[chord]               # the chord's root note in MIDI (key + scale degree offset)
            # minor chord (lowercase numeral) uses a minor third (+3)
            if chord.islower():
                third = root + 3
            # major chord (uppercase numeral) uses a major third (+4)
            else:
                third = root + 4
            fifth = root + 7
            chord_tones = [(root - 12), (third - 12), (fifth - 12), root, third, fifth]
            for harmony_note in range(8):

                candidates = []
                for t in chord_tones:
                    if t < melody[i]:
                        candidates.append(t)
                harmony_note = max(candidates)

                harmony.append(harmony_note)
                i += 1

    return harmony

def generate_saw(midi_note, tempo):
    fs = 48000                                              # sample rate in samples per second
    f = 440 * 2**((midi_note - 69) / 12)                    # convert MIDI note number to frequency in Hz
                                                            # A4 (midi 69) = 440Hz, each semitone multiplies by 2^(1/12)
    eighth_note_length = (60 / tempo) * 0.5                 # seconds, scaled by number of beats
    num_samples = int(fs * eighth_note_length)              # number of samples needed for one eighth note
                                                            # e.g. at 120bpm: 48000 * 0.25 = 12000 samples
    t = np.linspace(0, eighth_note_length, num_samples)     # time array from 0 to eighth note duration
    amplitude = np.iinfo(np.int16).max // 16                # 1/8 maximum 16-bit signed integer value (32767)
    data = amplitude * signal.sawtooth(2 * np.pi * f * t)   # generate sawtooth wave scaled to 16-bit amplitude
                                                            # signal.sawtooth() returns values in -1..1
    return data

def main():
    fs = 48000                                              # sample rate (samples per second)
    song = []                                               # holds the audio arrays for each note before joining
    bass = []
    harmony = []
    song_progression = {}                                   # maps each form letter to its chord progression

    # pick a random song form ex. ['A', 'A', 'B', 'B', 'C', 'C']
    form = get_song_form()
    if args.verbose:
        print("Form: ", form)

    # assign each unique letter its own chord progression (no repeats)
    for letter in form:
        if letter not in song_progression:
            song_progression[letter] = get_chord_progression()
    if args.verbose:
        for letter in form:
            print(song_progression[letter])

    # pick a random key (MIDI note A3-A4) and tempo (80-160 BPM)
    key = get_key()
    if args.verbose:
        print("Key: ", key)
    tempo = get_tempo()
    if args.verbose:
        print("Tempo: ", tempo, " BPM")

    # generate the full melody as a list of MIDI note numbers
    melody = get_melody(form, song_progression, key)

    # convert each MIDI note into a sawtooth wave and join them end to end
    for note in melody:
        song.append(generate_saw(note, tempo))
    #melody_song = np.concatenate(song)
    song = np.concatenate(song)

    # IF bass argument, add bass notes as eighth notes
    if args.bass:
        bass_line = get_bass_line(form, song_progression, key)
        for note2 in bass_line:
            # convert each MIDI bass note into a sawtooth wave and join them end to end
            bass.append(generate_saw(note2, tempo))
        bass_song = np.concatenate(bass)
        # join bass and melody
        song += bass_song

    if args.harmony:
        harmony_line = get_harmony(form, song_progression, key, melody)
        for note3 in harmony_line:
            harmony.append(generate_saw(note3, tempo))
        harmony_song = np.concatenate(harmony)
        song += harmony_song


    # write to wav file or play directly 
    if args.output:
        write(args.output, fs, song.astype(np.int16))
        if args.verbose:
            print(f"Success: Output saved to {args.output}")
    else:
        sd.play(song.astype(np.int16), fs)
        sd.wait()                               # block until playback ends

if __name__ == "__main__":
    main()