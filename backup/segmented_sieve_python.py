from __future__ import annotations
import math


BLOCK_SIZE: int = 10000


def main() -> int:
    N: int = int(100000)
    ROOT: int = int(math.sqrt(N))
    primes = []
    sieve = [True for _ in range(ROOT)]
    sieve[0] = False
    sieve[1] = False

    for number in range(2, ROOT):
        if sieve[number]:
            primes.append(number)

            for factor in range(number * number, ROOT, number):
                sieve[factor] = False

    rest_primes = []

    for block in range(ROOT, N, BLOCK_SIZE):
        sieve = [True for _ in range(BLOCK_SIZE + 1)]

        for prime in primes:
            first_factor = max(prime * prime, (block // prime) * prime)
            first_factor += prime if first_factor < block else 0

            for factor in range(first_factor, block + BLOCK_SIZE, prime):
                assert factor >= block
                sieve[factor - block] = False

        for number, sieve_state in enumerate(sieve):
            if sieve_state:
                rest_primes.append(block + number)

    print(f"{primes}, {len(primes)}, {rest_primes}, {len(rest_primes)}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
