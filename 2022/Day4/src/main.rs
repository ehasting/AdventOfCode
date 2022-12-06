extern crate core;

use std::env;
use std::fs;
use std::vec;
use core::str::Split;
use std::collections::HashMap;
use std::ops::Index;
use std::thread::current;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");



fn task1()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");
    let mut containscount: i32 =0;
    for line in lines
    {
        if line != ""
        {
            let mut ping: bool = true;
            //let res = line.split(",");
            let res: Vec<&str> = line.split(",").collect();
            let a: Vec<&str> = res.index(0).split("-").collect();
            let afrom = a.index(0).parse::<i32>().unwrap();
            let ato = a.index(1).parse::<i32>().unwrap();

            let b: Vec<&str> = res.index(1).split("-").collect();
            let bfrom = b.index(0).parse::<i32>().unwrap();
            let bto = b.index(1).parse::<i32>().unwrap();
            if afrom == bfrom
            {
                containscount += 1;
            }
            else if afrom < bfrom
            {
                //
                if bto <= ato
                {
                    containscount += 1;
                }
            }
            else
            {
                if ato <= bto
                {
                    containscount += 1;
                }
            }

        }
    }
    println!("Task1 contained ranges: {}", containscount);
}

fn task2()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");
    let mut containscount: i32 =0;
    for line in lines
    {
        if line != ""
        {
            let mut ping: bool = true;
            //let res = line.split(",");
            let res: Vec<&str> = line.split(",").collect();
            let a: Vec<&str> = res.index(0).split("-").collect();
            let afrom = a.index(0).parse::<i32>().unwrap();
            let ato = a.index(1).parse::<i32>().unwrap();

            let b: Vec<&str> = res.index(1).split("-").collect();
            let bfrom = b.index(0).parse::<i32>().unwrap();
            let bto = b.index(1).parse::<i32>().unwrap();

            if afrom == bfrom || ato == bto || afrom == bto || bfrom == ato
            {
                containscount += 1;
                println!("{}->{},{}->{}", afrom, ato, bfrom, bto);
            }
            else if ato > bfrom && bto > afrom
            {
                containscount += 1;
                println!("{}->{},{}->{}", afrom, ato, bfrom, bto);
            }


        }
    }
    println!("Task2 contained ranges: {}", containscount);
}

fn main() {
    task1();
    task2();
}
