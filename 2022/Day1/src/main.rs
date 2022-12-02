use std::env;
use std::fs;
use std::vec;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");

fn task1() {
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let split = payload_str.split("\n");
    let mut highest_elf: i32 = 0;
    let mut current_elf: i32 = 0;
    
    for num in split
    {

        if num == "" 
        { 
            // new elf
            if current_elf > highest_elf
            {
                highest_elf = current_elf
            }
            current_elf = 0;
        }
        else
        {
            let i = match num.parse::<i32>() {
                Ok(i) => i,
                Err(_e) => -1,
            };

            current_elf += i;
        }

    }
    println!("Phatezt elf: {}", highest_elf);
}

fn task2()
{
    let mut top_three: Vec<i32> = Vec::new();
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let split = payload_str.split("\n");
    let mut current_elf: i32 = 0;
    let mut total_three_elf: i32 = 0;
    top_three.push(0);
    top_three.push(0);
    top_three.push(0);
    for num in split
    {

        if num == "" 
        { 
             
            let minValue = *top_three.iter().min().unwrap();
            if  current_elf > minValue
            {
            //println!("Current elf: {}", current_elf);
            if let Some(index) = top_three.iter().position(|value| *value == minValue) {
                println!("Swap elf: {} -> {}", top_three[index], current_elf);
                top_three.swap_remove(index);
                top_three.push(current_elf);
            }
        }
            current_elf = 0;
        }
        else
        {
            let i = match num.parse::<i32>() {
                Ok(i) => i,
                Err(_e) => -1,
            };


            current_elf += i;
        }

    }
    for elf in top_three.iter()
    {
        println!("{}",elf);
        total_three_elf += elf;
    }
    println!("2: Phatezt elf: {}", total_three_elf);
}

fn main()
{
    task1();
    task2();
}
