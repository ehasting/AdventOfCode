extern crate core;

use std::env;
use std::fs;
use std::vec;
use core::str::Split;
use std::collections::HashMap;
use std::ops::Index;
use std::thread::current;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");

fn letterToPriority(letter: &char) -> u32
{
    //Lowercase item types a through z have priorities 1 through 26.
    //Uppercase item types A through Z have priorities 27 through 52.

    let n = *letter as u32;
    if n >= 65 && n <= 90
    {
        //println!("upper case: {}", letter);
        return (n - 64) + 26;
    }
    else if n >= 97 && n <= 122
    {
        //println!("lower case: {}", letter);
        return (n - 96);
    }
    panic!("errååår");
}

fn task1()
{

    let mut current_score = 0;
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");

    for line in lines
    {
        if line == ""
        {
            continue;
        }

        let mut shared_items = HashMap::new();
        let length = line.len();

        let storage1 = &line.to_string()[..length/2];
        let storage2 = &line.to_string()[length/2..];



        for item in storage1.chars()
        {
            if !storage2.find(item).is_none()
            {
                if !shared_items.contains_key(&item)
                {
                    shared_items.insert(item, item);
                }
            }
        }


        for item in shared_items
        {
            current_score += letterToPriority(&item.1);
        }




    }
    println!("Task1: {}", current_score);
}

fn task2()
{
    //let mut shared_items = HashMap::new();
    let mut current_score = 0;
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");
    let mut allbags: Vec<Vec<&str>> = Vec::new( );
    let mut currentbag: Vec<&str> = Vec::new();
    let mut index = 0;
    for line in lines
    {
        if line == ""
        {
            continue;
        }

        if index == 0
        {
            currentbag = Vec::new();
        }
        currentbag.push(line);

        index += 1;
        if index == 3
        {
            index = 0;
            allbags.push(currentbag.clone());
        }

    }


    for bag in allbags
    {
        let mut found_letters = HashMap::new();
        let line1 = bag.index(0);
        let line2 = bag.index(1);
        let line3 = bag.index(2);

        for item in line1.chars()
        {
            let find1 = !line2.find(item).is_none();
            let find2 = !line3.find(item).is_none();
            if find1 && find2
            {
                if !found_letters.contains_key(&item)
                {
                    found_letters.insert(item, item);
                    println!("letter: {}, score: {}", item, letterToPriority(&item));
                    current_score += letterToPriority(&item);
                }
            }
        }
    }

    println!("Task2: {}", current_score);
}

fn main() {
    task1();
    task2();
}
