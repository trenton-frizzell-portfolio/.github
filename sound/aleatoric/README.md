# Aleatoric Music Generator
Trenton Frizzell

This program procedurally generates aleatoric music using random number generation to guide song structure, then synthesizes the result with sawtooth waves.

The program:

* Randomly picks one of three song forms ("AABB/CC", "ABAB/CD", "AB/CDDD")
* Assigns each unique line letter its own randomly chosen four-chord progression, with no two letters sharing a progression (handled by shuffling the progression list and popping from it)
* Picks a random key (MIDI note in the A3-A4 range) and a random tempo (80-160 BPM)
* Generates an eighth-note melody, picking a note from the current chord with probability 0.8, otherwise a note from the major scale
* Converts each MIDI note to a frequency, synthesizes a sawtooth wave with scipy.signal.sawtooth, and joins the notes into one continuous audio array
* Plays the result directly through the speakers using sounddevice, or writes it to a WAV file (mono, 48000sps, 16-bit) when invoked with --output FILENAME.wav

Bonus features implemented

Bass (--bass): Adds a bass note (chord root, two octaves lower) layered under the melody
Harmony (--harmony): For each melody note, adds the closest chord tone at or below it, found by building chord tones across two octaves and taking the max that does not exceed the melody note

How It Went
The song-structure groundwork came together cleanly once I separated concerns: one function returns the ordered list of line letters, another returns a chord progression, and main() maps letters to progressions in a dictionary. Representing chords as Roman numerals and calculating roots/thirds/fifths from the key (rather than hardcoding every chord) kept the note logic compact.
The main challenges were:

Converting MIDI note numbers to frequencies and calculating the correct number of samples per note from the tempo
A case-sensitivity bug where lowercase chord numerals (e.g. iv) were missing from the scale-degree lookup
Combining multiple tracks (melody, bass, harmony) so they line up sample-for-sample, since independent int() truncation of note lengths can cause small length mismatches between tracks
Generating white noise correctly for percussion experiments (scaling to int16 amplitude before casting, and centering the noise around zero)

What Is Still To Be Done
The core assignment and the bass and harmony bonuses are complete. Remaining optional extras not yet implemented:

Rhythm (--rhythm): Random note patterns per verse/chorus instead of straight eighth notes
Percussion (--drums): White-noise drum track (prototype tested, not yet integrated)
MIDI (--midi): Acting as a MIDI controller via mido/python-rtmidi

Usage
python3 aleatoric.py [-o OUTPUT] [-b] [-a] [-v]

-o, --output FILENAME.wav — write the performance to a WAV file instead of playing it
-b, --bass — add a bass line
-a, --harmony — add harmony notes
-v, --verbose — print the generated form, progressions, key, and tempo
