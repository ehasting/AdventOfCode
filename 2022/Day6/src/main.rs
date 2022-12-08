use std::borrow::{Borrow, BorrowMut};
use std::collections::{HashMap, VecDeque};

static PAYLOAD: &'static [u8] = include_bytes!("./payload");

fn min(num1: &usize, num2: &usize) -> usize
{
    if num1 >= num2
    {
        return num2.clone() as usize;
    }
    return num1.clone() as usize;
}

fn task1()
{
    let mut ring_queue: Vec<char> = Vec::new();
    let mut ringqueue: [char; 3] = ['0', '0', '0'];
    ;
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let found_startofpacket: bool = false;
    let mut charcount = 0;
    let mut charcnt = 0;
    let allchar: Vec<char> = payload_str.chars().collect();
    let mut thestring: String = String::new();
    thestring.push_str(payload_str);
    for c in thestring.chars()
    {
        let n = *&thestring.len();
        let min = min(&n, &(&charcnt+&4));
        let currentslice = &thestring[charcnt..min];
        let mut found: bool = false;
        let mut lol: Vec<char> = currentslice.chars().collect();
        lol.sort();
        let mut check: HashMap<char, bool> = HashMap::new();
        println!("{}", c);
        for letter in lol
        {
            println!(" {}", letter);
            if !check.contains_key(&letter)
            {
                check.insert(letter, true);
            }
            else
            {
                found = true;
                break;
            }
        }
        if !found
        {
            println!("Found @ {}", charcnt +4);
            return;
        }
        charcnt = charcnt + 1;
    }


}

fn task2()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let found_startofpacket: bool = false;
    let mut charcount = 0;
    let mut charcnt = 0;
    let allchar: Vec<char> = payload_str.chars().collect();
    let mut thestring: String = String::new();
    thestring.push_str(payload_str);
    for c in thestring.chars()
    {
        let n = *&thestring.len();
        let min = min(&n, &(&charcnt+&14));
        let currentslice = &thestring[charcnt..min];
        let mut found: bool = false;
        let mut lol: Vec<char> = currentslice.chars().collect();
        lol.sort();
        let mut check: HashMap<char, bool> = HashMap::new();
        println!("{}", c);
        for letter in lol
        {
            println!(" {}", letter);
            if !check.contains_key(&letter)
            {
                check.insert(letter, true);
            }
            else
            {
                found = true;
                break;
            }
        }
        if !found
        {
            println!("Found @ {}", charcnt +14);
            return;
        }
        charcnt = charcnt + 1;
    }



}

fn main() {
    task1();
    task2();
}
