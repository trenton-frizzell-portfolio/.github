# 01_Clipped

## What I Did
Built a Python program that generates and manipulates audio samples using NumPy and SciPy.

1. **sine.wav** - Generates a 440Hz sine wave at ¼ maximum 16-bit amplitude (range -8192..8192), mono, 48000 samples/sec, 1 second duration.
2. **clipped.wav** - Generates a ½ amplitude sine wave and hard clips it at ¼ amplitude limits (-8192..8192), simulating a symmetrical diode hard clipper fuzz effect.
3. **Audio playback** - Plays the clipped sine wave directly to audio output using `sounddevice`, without reading back from a file.

## How It Went
The NumPy and SciPy integration was straightforward once I understood how to properly scale and cast sample data to int16. The main challenges were:
- Remembering to assign the return value of `np.clip()` rather than expecting in-place modification
- Understanding that `sounddevice` requires `sd.wait()` to prevent the program from exiting before playback finishes
- Setting up a virtual environment on macOS to install the required packages
