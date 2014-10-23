//! # Problem 2 from projecteuler.net
//!
//! You can find problem description [here][problem].
//!
//! [problem]: https://projecteuler.net/problem=2


fn sum_of_even_fibonacci_numbers(max_val: u64) -> u64
{
    let mut sum: u64 = 0;
    let mut current: u64 = 2;
    let mut previous: u64 = 1;

    while current < max_val {
        if current % 2 == 0 {
            sum += current;
        }

        current = current + previous;
        previous = current - previous;
    }

    return sum;
}

fn main()
{
    println!("{}", sum_of_even_fibonacci_numbers(4000000));
}
