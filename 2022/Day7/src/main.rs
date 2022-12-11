use std::borrow::{Borrow, BorrowMut};
use std::cell::{Cell, RefCell};
use std::collections::{HashMap, VecDeque};
use std::ops::{Add, Index};
use std::rc::{Rc, Weak};

static PAYLOAD: &'static [u8] = include_bytes!("./payload");


type SmartMyFs2000 = Rc<RefCell<MyFs2000>>;
#[derive(Clone)]
pub struct MyFs2000
{
    pub dir_name: Box<String>,
    pub sum_files: Cell<i32>,
    pub child_dirs: Vec<SmartMyFs2000>,
    pub sum_files_recursive: Cell<i32>,
    pub parent_dir_ref: Option<SmartMyFs2000>
}



impl MyFs2000
{
    pub fn new(dirname: String, parent: SmartMyFs2000) -> MyFs2000
    {
        let filesystem = MyFs2000 {
            dir_name: Box::new(dirname),
            sum_files: Cell::new(0),
            child_dirs: Vec::new(),
            sum_files_recursive: Cell::new(0),
            parent_dir_ref: Some(parent.clone())
        };
        return filesystem;
    }
    pub fn add_child(&mut self, child: SmartMyFs2000) {
        self.child_dirs.push(child);
    }
}

fn find_dir(dir_name: &String, fs: SmartMyFs2000) -> Option<SmartMyFs2000>
{
    let current_dir_name = fs.clone().into_inner().dir_name.clone();
    println!("{} == {}", current_dir_name, dir_name);
    if &current_dir_name.to_string() == dir_name
    {
        println!("Found {}", dir_name);
        return Some(fs.clone());
    }
    else {
        for n in fs.clone().get_mut().child_dirs.clone()
        {
            let n = find_dir(dir_name, n.clone());
            if n.is_some()
            {
                return n;
            }
            else {

            }
        }
        return None;
    }
}

fn traverse_and_accumulate_size(fs: Rc<MyFs2000>)
{
    if fs.child_dirs.is_empty()
    {
        println!("At end, calculating backwards");
        fs.sum_files_recursive.set(fs.clone().sum_files.get());
        //fs.clone().get_mut().sum_files_recursive.set(fs.clone().get_mut().sum_files.get());
    }
}


fn task1()
{
    let mut filesystem = MyFs2000 {
        dir_name: Box::new(String::from("/")),
        sum_files:  Cell::new(0),
        child_dirs: Vec::new(),
        sum_files_recursive: Cell::new(0),
        parent_dir_ref: Option::None
    };

    let root_fs = Rc::new(RefCell::new(filesystem));
    let mut current_fs: SmartMyFs2000 = root_fs.clone();
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split('\n');
    for line in lines
    {
        if line == ""
        {
            continue;
        }
        if line == "$ cd .."
        {
            // $ cd ..
            let new_fs = current_fs.clone().get_mut().parent_dir_ref.unwrap().clone();
            current_fs = new_fs;

        }
        else if line.contains("$ cd ")
        {
            // $ cd /


            let mut tmp = line.split(" ");
            tmp.next();
            tmp.next();
            let dir_name = tmp.next().unwrap().to_string();
            let found_dir = find_dir(&dir_name, root_fs.clone());
            if (found_dir.is_none())
            {
                panic!("{} not found?", dir_name);
            }
            current_fs = found_dir.unwrap();
        }

        else if line == "$ ls"
        {
            // $ ls
        }
        else if line.starts_with("dir")
        {
            // dir e
            let mut tmp = line.split(" ");
            tmp.next();
            let dir_name = tmp.next().unwrap().to_string();

            println!("Adding {}", &dir_name);
            current_fs.clone().get_mut().add_child( Rc::new(RefCell::new(MyFs2000::new(dir_name.clone(),current_fs.clone()))) );
        }
        else
        {
                    // 4060174 j
                    //calculate on current
                    let mut tmp = line.split(" ");
                    let val = tmp.next().unwrap().to_string();
                    //println!("{}", val);
                    let size = val.parse::<i32>().unwrap();
                    println!("adding size: {} to {}", size, current_fs.clone().get_mut().dir_name);
                    let currentsize = current_fs.clone().get_mut().sum_files.get();
                    current_fs.clone().get_mut().sum_files.set(currentsize + size);
                    //(*current_fs.as_ptr()).sum_files.set(currentsize + size);
        }
    }
    let mut megasum: i32 = 0;


    println!("task1 sum: {}", megasum);

}

fn task2()
{

}

fn main()
{
    task1();
    task2();
}
