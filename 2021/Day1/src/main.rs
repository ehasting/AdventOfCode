use std::env;
use std::fs;

static payload: &'static [u8] = include_bytes!("./payload");

fn part1()
{
    let payload_str = std::str::from_utf8(payload).unwrap();
    let mut split = payload_str.split("\n");
    let mut previous = -10;
    let mut highercount = 0;
    for num in split
    {
        if num != "" { 
            let mut ishigher = false;
            let i = match num.parse::<i32>() {
                Ok(i) => i,
                Err(_e) => -1,
            };
            if previous != -10
            {
                if i > previous {
                    highercount += 1;
                    ishigher = true;
                }
                println!("NUM: {} == {}", num, i);
            }
            previous = i;
        }
    }
    println!("Amount of increases: {}", highercount);   
}
struct GroupStruct 
{
    sum: i32,
    cnt: i32,
}

impl GroupStruct {
    fn add(&mut self, newsum: i32) {
        // ^^^ Here
        self.cnt += 1;
        self.sum += newsum;
    }
}

fn part2()
{
    let payload_str = std::str::from_utf8(payload).unwrap();
    let mut split = payload_str.split("\n");
    let mut previous = -10;
    let mut highercount = 0;
    let mut groups: Vec<GroupStruct>  = Vec::new();
    for num in split
    {
        if num != "" 
        {
            
            let mut i = match num.parse::<i32>() 
            {
                Ok(i) => i,
                Err(_e) => -1,
            };            
            for group in groups.iter_mut()
            {
                if group.cnt < 3
                {
                    group.add(i);
                }
            }
            let newgroup = GroupStruct {sum:i.clone(), cnt:1};
            groups.push( newgroup );
        }

    }
    for group in groups.iter_mut()
    {
        if group.cnt < 3
        {
            continue;
        }
        if previous != -10
        {
            if group.sum > previous {
                highercount += 1;
            }
            println!("NUM: {} ({})", group.sum, group.cnt);
        }
        previous = group.sum;
    }
    println!("Amount of increases: {}", highercount);  
}
fn main() {
    //part1();
    part2();
}
