use std::borrow::Borrow;

static PAYLOAD: &'static [u8] = include_bytes!("./payload");

fn has_sight_out(trees: &Vec<u32>, index: i32, row_length: i32) -> bool
{
    let rows = trees.len() as i32 / row_length;


    // first row
    if index <= row_length
    {
        return true;
    }

    let mut read_head: i32 = 0;
    for n in trees
    {
        // inner edge
        if ((read_head % row_length) + row_length) % row_length == 0
        {
            if read_head == index
            {
                println!("Edge number {}", index);
                return true;
            }
        }
        read_head = read_head + 1;
    }

    return false;
}

fn task1()
{
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split("\n");
    let mut linecount = 0;
    let mut first_round = true;
    let mut trees: Vec<u32> = Vec::new();
    for i in lines
    {
        if i == ""
        {
            continue;
        }
        for xx in i.chars()
        {
            trees.push(xx.to_digit(10).unwrap());
            if first_round
            {
                linecount = linecount + 1;
            }
            let num = xx.to_digit(10).unwrap();
        }
        first_round =false;
    }
    let mut reader_head: i32 = 0;
    let mut running_counter: i32 = 0;
    //print!(" {:2} |", 0);
    for lol in &trees
    {
        //print!("{} ", lol);
        has_sight_out(&trees, *lol as i32, linecount);
        reader_head = reader_head + 1;

        running_counter = running_counter + 1;
        if reader_head == linecount
        {
            //print!("\n {:2} |", running_counter);
            reader_head = 0;
        }
    }
}

fn main() {
    task1();
}
