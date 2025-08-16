from __future__ import annotations
import datetime
from typing import (
    Final,
)


LIMIT: Final[int] = 20000


def generate_primes(limit: int) -> list[int]:
    sieve = [True for _ in range(limit + 1)]
    primes = []
    
    for number in range(2, limit):
        if sieve[number]:
            primes.append(number)
            
            for factor in range(number * number, limit + 1, number):
                sieve[factor] = False

    return primes


def main() -> int:
    primes = generate_primes(LIMIT)            
    prime_months = set(primes[:5])
    date, given_day, string_N = input().split()
    N, year, month, day = map(int, (string_N, date[:4], date[4:6], date[6:]))
    current_date = datetime.date(year, month, day)
    
    for prime in primes:
        next_date = current_date + datetime.timedelta(days=prime)

        if next_date.strftime("%a") == given_day and next_date.month in prime_months:
            print(f"{'No' if prime > N else 'Yes'} {prime}")
            return 0

    print("No 0")

    return 0
    
    
if __name__ == "__main__":
    raise SystemExit(main())
