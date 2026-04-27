import argparse
import numpy as np
from scipy.io.wavfile import read

parser = argparse.ArgumentParser()
parser.add_argument("input", help="Path to input file")
parser.add_argument("-v", "--verbose", action="store_true", help="Make the operation more talkative")
args = parser.parse_args()

if args.verbose:
    print(f"Verbose enabeled")
    print(f"    File name:   {args.input}")

def load_wav() -> int | list[int]:
    fs, data = read(args.input)
    if args.verbose:
        print(f"    sample rate: {fs}")
        #print(f"number of channels = {data.shape[1]}")
        length = data.shape[0] / fs
        print(f"    length:      {length:.2f}s")

    return fs, data

def tone_power(samples, N, f, fs):
    I = 0
    Q = 0
    for n in range(N):
        angle = (2 * (np.pi) * f * n) / fs
        I = I + samples[n] * np.cos(angle)
        Q = Q + samples[n] * np.sin(angle)
    return np.square(I) + np.square(Q)

def write(list):
    with open("message.txt", "w") as f:
        f.write(''.join(list) + '\n')


def main():
    f1 = 2225
    f2 = 2025
    j = 0
    message = []

    # Load the .wav file contents.
    fs, data = load_wav()

    # cut array down to the number of bits present(Bits are 160 samples long)
    total_bits = data.shape[0] // 160
    # for i in number of bits send to tone_power
    for i in range(total_bits):
        if args.verbose: 
            print(f"Bit: {i}")
        # calculate start and end point of the bit
        start = i * 160
        end = start + 160
        # split the data into said bit section (0-159; 160-319)
        bit = data[start:end]
        # convert 
        bit = bit.astype(np.float64) / 32768.0
        # set Power to the return from the function
        mark = tone_power(bit, 160, f1, fs)
        space = tone_power(bit, 160, f2, fs) 

        if args.verbose: 
            print(f"    power1: {mark}")
            print(f"    power2: {space}")

        if j == 0: 
            newlist = []
            j += 1
        elif j > 0 and j < 9:
            if (mark > space):
                newlist.insert(0, "1")
            else:
                newlist.insert(0, "0")
            j += 1
        else:
            # convert and append
            result = "".join(newlist)
            int_result = int(result, 2)
            chr_result = chr(int_result)
            message.append(chr_result)
            j = 0

    write(message) 



if __name__=="__main__":
    main()