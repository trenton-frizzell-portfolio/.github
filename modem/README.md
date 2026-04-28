# modem.py

This program decodes audio files encoded using the Bell 103 modem protocol and outputs the decoded ASCII message to message.txt.

Reads a 48kHz 16-bit mono WAV file using scipy.io.wavfile
Converts samples to floating point in the range -1..1
Splits the audio into 160-sample blocks (one per bit)
Uses an I/Q correlator (tone_power) to detect whether each block contains a 2025Hz (space/0) or 2225Hz (mark/1) tone by comparing their powers
Frames the bits into 8N1 bytes (skipping start and stop bits, collecting 8 data bits in LSB-first order)
Converts each byte to an ASCII character and writes the result to message.txt

The tone detector came together quickly once I understood the I/Q correlator math. I did have some challenges. Getting the framing logic right - tracking position within each 10-bit frame using a counter and correctly skipping start/stop bits - took some work. Understanding LSB-first bit order and using insert(0, ...) to reverse bit order when building each byte was easy to figure out when it produced garbage the first time. I should have paid attention to this more to start with. As I'm not very proficient with python, managing where binary-to-character conversion happened relative to collecting the full message list was a challenge.

The program was verified against both provided test files:

```sh
trentonfrizzell@trentons-MacBook-Pro 02 % python3 modem.py test1.wav             
trentonfrizzell@trentons-MacBook-Pro 02 % cat message.txt                        
Come here, Watson, I can hear you now
trentonfrizzell@trentons-MacBook-Pro 02 % python3 modem.py test2.wav             
trentonfrizzell@trentons-MacBook-Pro 02 % cat message.txt           
What hath God wrought?
```

Decoded from message.wav:
```sh
trentonfrizzell@trentons-MacBook-Pro 02 % python3 modem.py message.wav
trentonfrizzell@trentons-MacBook-Pro 02 % cat message.txt             
You will engage in a profitable business activity.
```

## Usage

`python3 modem.py [-h] [-v] input`

input — path to the input WAV file
-v, --verbose — print sample rate, file length, and per-bit detector powers
