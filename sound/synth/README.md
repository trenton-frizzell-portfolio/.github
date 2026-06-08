# MIDI Synthesizer

Trenton Frizzell

Program is a real-time monophonic software synthesizer in Python. It listens for MIDI key events from a controller and generates audio on the fly, sending it to the system's default output.

The program:
- Opens a MIDI input port with `mido` (routed from VMPK through the macOS IAC Driver) and reads key events in a loop with `iter_pending()`
- Treats `note_on` with velocity > 0 as KEY ON, and both `note_off` and `note_on` with velocity 0 as KEY OFF
- Generates audio in real time using a `sounddevice` `OutputStream` callback that fills each buffer on demand, keeping waveform phase continuous across buffers via a running sample index
- Synthesizes a sawtooth wave at -3dBFS (amplitude ~0.708)
- Applies a fixed AR (attack/release) envelope implemented as a class: 10ms linear ramp up on note start and 10ms linear ramp down on note release (480 samples each at 48kHz), with the envelope state persisting across callback buffers
- **Velocity → volume:** KEY ON velocity scales the note's volume, using a squared curve for a more natural loudness response
- **Alternate waveforms (`--wave`):** Selectable sawtooth (default), sine, square, or triangle via a command-line argument

## How It Went
The biggest conceptual shift from previous assignments was moving from "compute the whole song, then play it" to real-time generation, where an audio callback runs continuously in its own thread and a separate MIDI loop updates shared state (current frequency, velocity, envelope stage) that the callback reads each buffer.

The main challenges were:
- Understanding the callback/threading model: the audio callback only reads shared state and never touches MIDI, while the MIDI loop only writes shared state and never generates audio
- Keeping waveform phase continuous between buffers using a running sample index
- Designing the AR envelope as a small state machine (attack → sustain → release → off) whose state persists across callback calls, so releases ramp down smoothly instead of cutting off and clicking
- Setting up virtual MIDI on macOS (enabling the IAC Driver and routing VMPK's output to it) so the program had a controller to listen to

## Still To Be Done
The core assignment and the velocity and alternate-waveform bonuses are complete. Known limitations and unimplemented extras:
- **Fast re-triggering bug:** Because the synth is monophonic with a single shared envelope and frequency, pressing a new note before the previous note finishes releasing can cause the new note to be dropped or cut off. Proper polyphony (a separate voice/oscillator/envelope per note) would resolve this.
- **Remaining bonus features not implemented:** direct named MIDI device selection, KEY OFF velocity controlling release time, response to other MIDI control-change messages, a noise source, a full ADSR envelope (decay + sustain level), and polyphony.

## Usage
```
python3 synth.py [--wave {saw,sine,square,triangle}]
```
- `--wave` — waveform to synthesize (default: saw)

Requires a MIDI controller routed to the input port (e.g. VMPK → IAC Driver Bus 1 on macOS). Press Ctrl+C to quit.
