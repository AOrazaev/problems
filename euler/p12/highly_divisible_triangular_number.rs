//! # Problem 12 from projecteuler.net
//!
//! You can find problem description [here][problem].
//!
//! [problem]: https://projecteuler.net/problem=12


mod factorization {

use std::collections::HashMap;

fn ferma_factorization(number: u64) -> (u64, u64)
{
    assert!(number % 2 != 0);
    let mut x = (number as f64).sqrt().ceil() as u64;

    if x == number {
        return (x, 1);
    }

    loop {
        let y = ((x * x - number) as f64).sqrt();
        if y == y.round() {
            return (x - y as u64, x + y as u64);
        }
        x += 1;
    }
}

fn map_incr(map: &mut HashMap<u64, u64>, key: u64) {
        if map.contains_key(&key) {
            *map.get_mut(&key) += 1;
        } else {
            map.insert(key, 1);
        }
}

fn recoursive_factorization(map: &mut HashMap<u64, u64>, mut num: u64) {
    while num % 2 == 0 {
        map_incr(map, 2);
        num /= 2;
    }

    if num == 1 {
        return;
    }

    let factorization = ferma_factorization(num);
    if num == factorization.val0() {
        map_incr(map, num);
    } else {
        recoursive_factorization(map, factorization.val0());
    }

    if num == factorization.val1() {
        map_incr(map, num);
    } else {
        recoursive_factorization(map, factorization.val1());
    }
}

pub fn fast_number_of_divisors(number: u64) -> u64
{
    let mut map: HashMap<u64, u64> = HashMap::new();

    recoursive_factorization(&mut map, number);
    let mut result = 1u64;

    for val in map.values() {
        result *= val + 1;
    }
    return result;
}

fn number_of_divisors(value: u64) -> u64
{
    let mut result = 1;
    let mut current = 1;

    while current < value {
        if value % current == 0 {
            result += 1;
        }
        current += 1;
    }

    return result;
}

#[allow(dead_code)]
pub fn stress_test(n: u64) { 
    for n in range(1u64, n) {
        let fast = fast_number_of_divisors(n);
        let slow = number_of_divisors(n);
        if fast != slow {
            println!("n = {}\tgot {}\texpect {}", n, fast, slow);
        }
    }
    println!("TEST OK!");
}

} // mod factorization


fn calc_triangular(num: u64) -> u64
{
    return num * (num + 1) / 2;
}

fn triangular_number_from_divisors(num_divisors: u64) -> u64
{
    let mut current: u64 = 1;
    loop {
        let triangular = calc_triangular(current);
        let triangular_divisors = factorization::fast_number_of_divisors(triangular);

        if triangular_divisors > num_divisors {
            return triangular;
        }

        current += 1;
    }
}

fn main()
{
    factorization::stress_test(500);
    
    println!("{}", triangular_number_from_divisors(500));
}
