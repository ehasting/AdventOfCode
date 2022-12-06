extern crate core;

use std::env;
use std::fs;
use std::vec;
use core::str::Split;
use std::borrow::{Borrow, BorrowMut};
use std::collections::HashMap;
use std::ops::Index;
use std::thread::current;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");




fn task1()
{

    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");

    let mut stackmap = HashMap::new();

    let mut setup_phase: bool = true;
    let skipwhite = 4;
    let mut stacklines: Vec<&str> = Vec::new();
    for line in lines
    {

        if line == "" && setup_phase
        {
            // Process data
            stacklines.reverse();
            let n: Vec<&str> = stacklines.index(0).trim().split_whitespace().collect();
            for num in n
            {
                if num != ""
                {
                    stackmap.insert(num.parse::<i32>().unwrap(), format!("{}", ""));
                }
            }

            for stacks in &stacklines[1..]
            {
                let mut stackmapindex = 1;
                let n: Vec<&str> = stacks.split(" ").collect();
                let mut inwhitespace = false;
                let mut whitespacecount = 0;
                for test in n
                {
                    if (test != "")
                    {
                        stackmap.entry(stackmapindex).or_insert_with(String::new).push_str(test);
                        stackmapindex = stackmapindex +1 ;

                    }
                    else if inwhitespace
                    {
                        whitespacecount = whitespacecount + 1;
                        if whitespacecount == 4
                        {
                            inwhitespace = false;
                            stackmapindex = stackmapindex +1 ;
                        }
                    }
                    else
                    {
                        inwhitespace = true;
                        whitespacecount = 1;
                    }

                }
            }
            /*
            for l in &stacklines
            {
                println!("{}", l);
            }
*/
            for map in stackmap.to_owned().iter()
            {
                let mut finalstack: String = String::new();
                (for ch in map.1.chars()
                {
                    if ch != '[' && ch != ']'
                    {
                        finalstack.push(ch);
                        println!("{}", ch);
                    }

                });

                stackmap.get_mut(map.0).and_then(|inner| Some(*inner = finalstack));

            }
            setup_phase = false;
            continue;
        }

        if setup_phase
        {
            stacklines.push(line);
            //println!(" {}", line);
        }
        else // worker phase
        {
            if line == ""
            {
                continue;
            }
            // move 1 from 2 to 1
            let res: Vec<&str> = line.split(" ").collect();
            let amount = res.index(1).parse::<i32>().unwrap();
            let row_from = res.index(3).parse::<i32>().unwrap();
            let row_to = res.index(5).parse::<i32>().unwrap();
            let mut current_from_value = stackmap.get(&row_from).unwrap().clone();

            println!("Move from {} {} {}", row_from, amount, row_to);

            for i in 0..amount
            {
                stackmap.entry(row_to).or_insert_with(String::new).push(current_from_value.pop().unwrap());
            }
            *stackmap.entry(row_from).or_insert("".to_string()) = current_from_value.clone();



        }

        if line != ""
        {
            let mut ping: bool = true;
            //let res = line.split(",");
            let res: Vec<&str> = line.split(",").collect();
            let a: Vec<&str> = res.index(0).split("-").collect();


        }
    }
    let mut count_vec: Vec<_> = stackmap.iter().collect();
    count_vec.sort();
    for n in count_vec
    {
        print!("{}", n.1.chars().last().unwrap());
    }
    println!("");
    println!("Task1 contained ranges: {}", setup_phase);
}

fn task2()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");

    let mut stackmap = HashMap::new();

    let mut setup_phase: bool = true;
    let skipwhite = 4;
    let mut stacklines: Vec<&str> = Vec::new();
    for line in lines
    {

        if line == "" && setup_phase
        {
            // Process data
            stacklines.reverse();
            let n: Vec<&str> = stacklines.index(0).trim().split_whitespace().collect();
            for num in n
            {
                if num != ""
                {
                    stackmap.insert(num.parse::<i32>().unwrap(), format!("{}", ""));
                }
            }

            for stacks in &stacklines[1..]
            {
                let mut stackmapindex = 1;
                let n: Vec<&str> = stacks.split(" ").collect();
                let mut inwhitespace = false;
                let mut whitespacecount = 0;
                for test in n
                {
                    if (test != "")
                    {
                        stackmap.entry(stackmapindex).or_insert_with(String::new).push_str(test);
                        stackmapindex = stackmapindex +1 ;

                    }
                    else if inwhitespace
                    {
                        whitespacecount = whitespacecount + 1;
                        if whitespacecount == 4
                        {
                            inwhitespace = false;
                            stackmapindex = stackmapindex +1 ;
                        }
                    }
                    else
                    {
                        inwhitespace = true;
                        whitespacecount = 1;
                    }

                }
            }
            /*
            for l in &stacklines
            {
                println!("{}", l);
            }
*/
            for map in stackmap.to_owned().iter()
            {
                let mut finalstack: String = String::new();
                (for ch in map.1.chars()
                {
                    if ch != '[' && ch != ']'
                    {
                        finalstack.push(ch);
                        println!("{}", ch);
                    }

                });

                stackmap.get_mut(map.0).and_then(|inner| Some(*inner = finalstack));

            }
            setup_phase = false;
            continue;
        }

        if setup_phase
        {
            stacklines.push(line);
            //println!(" {}", line);
        }
        else // worker phase
        {
            if line == ""
            {
                continue;
            }
            // move 1 from 2 to 1
            let res: Vec<&str> = line.split(" ").collect();
            let amount = res.index(1).parse::<i32>().unwrap();
            let row_from = res.index(3).parse::<i32>().unwrap();
            let row_to = res.index(5).parse::<i32>().unwrap();
            let mut current_from_value = stackmap.get(&row_from).unwrap().clone();

            println!("Move from {} {} {}", row_from, amount, row_to);
            stackmap.entry(row_to).or_insert_with(String::new).push_str(&current_from_value[(current_from_value.len() - amount as usize) as usize..]);
            for i in 0..amount
            {
                current_from_value.pop();
            }
            *stackmap.entry(row_from).or_insert("".to_string()) = current_from_value.clone();



        }

        if line != ""
        {
            let mut ping: bool = true;
            //let res = line.split(",");
            let res: Vec<&str> = line.split(",").collect();
            let a: Vec<&str> = res.index(0).split("-").collect();


        }
    }
    let mut count_vec: Vec<_> = stackmap.iter().collect();
    count_vec.sort();
    for n in count_vec
    {
        print!("{}", n.1.chars().last().unwrap());
    }
    println!("");
    println!("Task2 contained ranges: {}", setup_phase);
}

fn main() {
    task1();
    task2();
}
