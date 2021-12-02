use std::env;
use std::fs;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");

fn part1()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let split = payload_str.split("\n");
    let mut horizontal = 0;
    let mut depth = 0;
    for command in split
    {
        let tuplet = command.split(" ").collect::<Vec<&str>>();
        let cmd = String::from(tuplet[0]);
        let qty = match tuplet[1].parse::<i32>() {
            Ok(i) => i,
            Err(_e) => -1,
        };

        match cmd.as_str() 
        {
            "down" => depth += qty,
            "up" => depth -= qty,
            "forward" => horizontal += qty,
            _ => horizontal = horizontal
        }

    }
    println!("Depth: {}, Horizontal: {}, SUM: {}", depth, horizontal, (depth*horizontal));
}

fn part2()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let split = payload_str.split("\n");
    let mut horizontal = 0;
    let mut depth = 0;
    let mut aim = 0;
    for command in split
    {
        let tuplet = command.split(" ").collect::<Vec<&str>>();
        let cmd = String::from(tuplet[0]);
        let qty = match tuplet[1].parse::<i32>() {
            Ok(i) => i,
            Err(_e) => -1,
        };

        match cmd.as_str() 
        {
            "down" => 
            { 
                aim += qty
            },
            "up" => 
            {
                aim -= qty
            }
            "forward" => 
            {
                depth += qty * aim;
                horizontal += qty
            }
            _ => horizontal = horizontal
        }

    }
    println!("Depth: {}, Horizontal: {}, SUM: {}", depth, horizontal, (depth*horizontal));
}

fn main() {
    part1();
    part2();
}
