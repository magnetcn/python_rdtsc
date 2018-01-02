# encoding: utf-8
import time
import rdtsc

def test_basic():
    start = rdtsc.rdtsc()
    time.sleep(1)
    end = rdtsc.rdtsc()
    print('time elapsed:',end-start)

if __name__ == '__main__':
    test_basic()

