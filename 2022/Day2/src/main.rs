extern crate core;

use std::env;
use std::fs;
use std::vec;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");

#[derive(PartialEq)]
#[derive(Copy, Clone)]
#[derive(Debug)]
enum Type
{
    Rock,
    Scissors,
    Paper
}

#[derive(PartialEq)]
#[derive(Debug)]
enum Outcome
{
    Win,
    Draw,
    Loss
}

fn getType(letter: &str) -> Type
{
    match letter {
        "A" | "X" => return Type::Rock,
        "B" | "Y" => return Type::Paper,
        "C" | "Z" => return Type::Scissors,
        _ => panic!("lol")
    }
}

fn getExpectedOutcome(letter: &str) -> Outcome
{
    match letter {
        "X" => return Outcome::Loss,
        "Y" => return Outcome::Draw,
        "Z" => return Outcome::Win,
        _ => panic!("lol")
    }
}

fn DoGame(me: &Type, enemy: &Type) -> i32
{
    let WIN: i32 = 6;
    let LOSS: i32 = 0;
    let DRAW: i32 = 3;
    let type_score = match me {
        Type::Rock => {
            1
        },
        Type::Paper =>2,
        Type::Scissors => 3,
        _ => panic!("")
    };

    let mut result_score: i32 = 0;
    if me == enemy
    {
        result_score = DRAW;
    }
    else
    {
        if *me == Type::Rock
        {
            result_score = match enemy {
                Type::Scissors => WIN,
                Type::Paper => LOSS,
                _ => panic!("")
            }
        }
        else if *me == Type::Paper
        {
            result_score = match enemy {
                Type::Rock => WIN,
                Type::Scissors => LOSS,
                _ => panic!("")
            }
        }
        else if *me == Type::Scissors
        {
            result_score = match enemy {
                Type::Paper => WIN,
                Type::Rock => LOSS,
                _ => panic!("")
            }
        }
    }
    println!("{:?} vs {:?} = {} + {}", enemy, me, result_score, type_score);
    return (result_score + type_score);
}

fn DetermineOutcome(expectedOutcome: &Outcome, enemy: &Type) -> Type
{
    if *expectedOutcome == Outcome::Draw
    {
        let rval = enemy.to_owned();
        return rval11373;
    }
    if *expectedOutcome == Outcome::Loss
    {
        match enemy {
            Type::Scissors => return Type::Paper,
            Type::Paper => return Type::Rock,
            Type::Rock => return Type::Scissors
        }
    }
    if *expectedOutcome == Outcome::Win
    {
        match enemy {
            Type::Scissors => return Type::Rock,
            Type::Paper => return Type::Scissors,
            Type::Rock => return Type::Paper
        }
    }
    panic!("lol");
}


fn task1()
{

    let mut the_score: i32 = 0;
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let split = payload_str.split("\n");
    
    for line in split
    {
        if line != ""
        {
            let mut ping: bool = true;
            let res = line.split(" ");
            let mut enemy = Type::Scissors;
            let mut me = Type::Scissors;
            for n in res
            {
                if ping
                {
                    enemy = getType(n);
                    ping = false;
                }
                else
                {
                    me = getType(n);
                }
            }
            the_score += DoGame(&me, &enemy);

        }
    }
    println!("Task1: Score: {}", the_score);

}

fn task2()
{
    let mut the_score: i32 = 0;
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let split = payload_str.split("\n");

    for line in split
    {
        if line != ""
        {
            let mut ping: bool = true;
            let res = line.split(" ");
            let mut enemy = Type::Scissors;
            let mut me = Type::Scissors;
            let mut expectedOutcome = Outcome::Loss;
            for n in res
            {
                if ping
                {
                    enemy = getType(n);
                    ping = false;
                }
                else
                {
                    expectedOutcome = getExpectedOutcome(n);
                }
            }
            me = DetermineOutcome(&expectedOutcome, &enemy);
            the_score += DoGame(&me, &enemy);

        }
    }
    println!("Task2: Score: {}", the_score);
}

fn main()
{
    task1();
    task2();
}
