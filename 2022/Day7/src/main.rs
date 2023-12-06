use std::borrow::{Borrow, BorrowMut};
use std::cell::{Cell, RefCell};
use std::cmp::max;
use std::collections::{HashMap, VecDeque};
use std::ops::{Add, Deref, Index};
use std::rc::{Rc, Weak};

static PAYLOAD: &'static [u8] = include_bytes!("./payload");


type SmartMyFs2000 = Rc<RefCell<MyFs2000>>;

#[derive(Clone)]
pub struct MyFs2000
{
    pub dir_name: String,
    pub sum_files: Cell<i64>,
    pub child_dirs: RefCell<Vec<SmartMyFs2000>>,
    pub sum_files_recursive: Cell<i64>,
    pub parent_dir_ref: Option<SmartMyFs2000>,
}


impl MyFs2000
{
    pub fn new(dir_name: String, parent: SmartMyFs2000) -> MyFs2000
    {
        let filesystem = MyFs2000 {
            dir_name: dir_name,
            sum_files: Cell::new(0),
            child_dirs: RefCell::new(Vec::new()),
            sum_files_recursive: Cell::new(0),
            parent_dir_ref: Some(parent.clone()),
        };
        return filesystem;
    }
}

fn change_dir(dir_name: String, fs: SmartMyFs2000) -> Option<SmartMyFs2000>
{
    if dir_name == "/"
    {
        return Some(fs.clone());
    }
    let mut current_obj_ref = &(*fs.try_borrow().unwrap()).child_dirs;

    for n in current_obj_ref.borrow().iter()
    {
        let current_child_dir_name = &(*n.try_borrow().unwrap()).dir_name;
        if current_child_dir_name == &dir_name
        {
            return Some(n.clone());
        }
    }
    panic!("change_dir: No dir named {}", dir_name);
}

fn search_for_delete_object(fs: &SmartMyFs2000, target: i64, total_size: i64, mut lowest_dir_size: Rc<Cell<i64>>)
{
    let current_recursive_size = &(*fs.try_borrow().unwrap()).sum_files_recursive.get();
    let lowest_dir = lowest_dir_size.clone().get();

    if (total_size + current_recursive_size >= target) && current_recursive_size < &lowest_dir && total_size + current_recursive_size > 0
    {
        lowest_dir_size.set(*current_recursive_size);
    }

    let dirs = &(*fs.try_borrow().unwrap()).child_dirs;

    if  (*dirs.try_borrow_mut().unwrap()).is_empty()
    {
        //println!("end of line");
    }
    else
    {
        let mut current_obj_ref = &(*fs.try_borrow().unwrap()).child_dirs;
        for n in current_obj_ref.borrow().iter()
        {
            search_for_delete_object(n, target, total_size, lowest_dir_size.clone());
        }
    }
}

fn acc_folder_lower_then(fs: &SmartMyFs2000, max_size: i64, mut sum: Rc<Cell<i64>>)
{
    let mut current_sum: i64 = 0;
    let current_dir_name = &(*fs.try_borrow().unwrap()).dir_name;
    let current_recursive_size = &(*fs.try_borrow().unwrap()).sum_files_recursive.get();

    if current_recursive_size <= &max_size
    {
        sum.set(sum.get() + current_recursive_size);
    }

    let dirs = &(*fs.try_borrow().unwrap()).child_dirs;

    if  (*dirs.try_borrow_mut().unwrap()).is_empty()
    {
        //println!("end of line");
    }
    else
    {
        let mut current_obj_ref = &(*fs.try_borrow().unwrap()).child_dirs;
        for n in current_obj_ref.borrow().iter()
        {
            acc_folder_lower_then(n, max_size, sum.clone());
        }
    }
}

fn reverse_traverse(fs: &SmartMyFs2000, prev_size: i64, mut sum: Rc<Cell<i64>>)
{
    let current_size = &(*fs.try_borrow().unwrap()).sum_files.get();
    let recursive_sum = current_size + prev_size;
    let _ = &(*fs.try_borrow().unwrap()).sum_files_recursive.set(recursive_sum);
    let new_sum =  sum.clone().get() + recursive_sum;
    if recursive_sum <= 100000
    {

        sum.set(new_sum);
    }

    if  (*fs.try_borrow().unwrap()).parent_dir_ref.borrow().is_some()
    {
        let nn = &(*fs.try_borrow().unwrap()).parent_dir_ref;
        reverse_traverse(&nn.clone().unwrap(), recursive_sum, sum.clone());
    }
}
fn traverse_and_accumulate_size(fs: &SmartMyFs2000, mut tot: Rc<Cell<i64>>)
{
    let mut current_sum: i64 = 0;
    let current_dir_name = &(*fs.try_borrow().unwrap()).dir_name;
    let dirs = &(*fs.try_borrow().unwrap()).child_dirs;
    let current_size = &(*fs.try_borrow().unwrap()).sum_files.get();

    if  (*dirs.try_borrow_mut().unwrap()).is_empty()
    {
        reverse_traverse(fs, 0, tot);
    }
    else
    {
        let mut current_obj_ref = &(*fs.try_borrow().unwrap()).child_dirs;

        for n in current_obj_ref.borrow().iter()
        {
            traverse_and_accumulate_size(n, tot.clone());
        }
    }
}


fn task1()
{
    let mut indent:usize = 0;
    let mut filesystem = MyFs2000 {
        dir_name: String::from("/"),
        sum_files: Cell::new(0),
        child_dirs: RefCell::new(Vec::new()),
        sum_files_recursive: Cell::new(0),
        parent_dir_ref: Option::None,
    };

    let root_fs = Rc::new(RefCell::new(filesystem));
    let mut current_fs = root_fs.clone();
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split('\n');
    let mut count: i32 = 0;
    for line in lines
    {
        count = count + 1;
        if line == ""
        {
            continue;
        }
        if line == "$ cd .."
        {
            let mut old_dir_name = String::from("");
            {
                old_dir_name = (*current_fs.try_borrow().unwrap()).dir_name.clone();
            }
            indent = indent - 4;
            // $ cd ..
            let old_fs = current_fs.clone();
            let is_next =  (*old_fs.try_borrow().unwrap()).parent_dir_ref.clone();
            if is_next.is_some()
            {
                current_fs = is_next.unwrap();
            }
            else {
                panic!("Failed to navigate up a level");
            }
            {

                let dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
                // println!("{:indent$}{} DIR-Changed OUT {} -> {}", "", count, old_dir_name, dir_name, indent=indent);
            }

        }
        else if line.starts_with("$ cd")
        {
            // $ cd /

            indent = indent + 4;
            let mut tmp = line.split(" ");
            tmp.next();
            tmp.next();
            let dir_name = tmp.next().unwrap().to_string();

            let found_dir = change_dir(dir_name.clone(), current_fs.clone());
            if (found_dir.is_none())
            {
                let current_dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
                panic!("{} not found? at {}", dir_name, current_dir_name);
            }
            else {
                current_fs = found_dir.unwrap();
            }

            {
                let dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
                // println!("{:indent$}{} DIR-Changed IN to {}", "", count, dir_name, indent=indent);
            }
        }
        else if line == "$ ls"
        {
            // $ ls
        }
        else if line.starts_with("dir")
        {
            let current_dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
            // dir e
            let mut tmp = line.split(" ");
            tmp.next();
            let dir_name = tmp.next().unwrap().to_string();
            //println!("{:indent$}Adding {}", "", &dir_name, indent=indent);
            let new_data = Rc::new(RefCell::new(MyFs2000::new(dir_name.clone(), current_fs.clone())));
            let xx = &(*current_fs.try_borrow().unwrap()).child_dirs;
            let _ = &(*xx.try_borrow_mut().unwrap()).push(new_data.clone());
            // println!("{:indent$}{} adding {} to {}", "", count, dir_name, current_dir_name, indent=indent);
        }
        else
        {
            // 4060174 j
            //calculate on current
            let mut tmp = line.split(" ");
            let val = tmp.next().unwrap().to_string();
            //println!("{}", val);
            let size = val.parse::<i64>().unwrap();
            let dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
            //println!("{:indent$}adding size: {} to {}", "", size, dir_name, indent=indent);
            let currentsize = &(*current_fs.try_borrow().unwrap()).sum_files.get();
            let _ = &(*current_fs.try_borrow().unwrap()).sum_files.set(currentsize + size);
            //(*current_fs.as_ptr()).sum_files.set(currentsize + size);
        }
    }
    //let mut megasum: i32 = 0;

    let megasum: Rc<Cell<i64>> = Rc::new(Cell::new(0));
    traverse_and_accumulate_size(&root_fs, megasum.clone());
    let sum = Rc::new(Cell::new(0));
    acc_folder_lower_then(&root_fs, 100000, sum.clone());
    println!("task1 sum: {}", sum.get());
}

fn task2_reverse_traverse(fs: &SmartMyFs2000, prev_size: i64)
{
    let current_size = &(*fs.try_borrow().unwrap()).sum_files.get();
    let current_recursive_size = &(*fs.try_borrow().unwrap()).sum_files_recursive.get();
    let recursive_sum = current_size + prev_size + current_recursive_size;
    let _ = &(*fs.try_borrow().unwrap()).sum_files_recursive.set(recursive_sum);

    if  (*fs.try_borrow().unwrap()).parent_dir_ref.borrow().is_some()
    {
        let nn = &(*fs.try_borrow().unwrap()).parent_dir_ref;
        task2_reverse_traverse(&nn.clone().unwrap(), recursive_sum);
    }
}

fn task2_traverse_and_accumulate_size(fs: &SmartMyFs2000)
{
    let mut current_sum: i32 = 0;
    let current_dir_name = &(*fs.try_borrow().unwrap()).dir_name;
    let dirs = &(*fs.try_borrow().unwrap()).child_dirs;
    let current_size = &(*fs.try_borrow().unwrap()).sum_files.get();

    if  (*dirs.try_borrow_mut().unwrap()).is_empty()
    {
        task2_reverse_traverse(fs, 0);
    }
    else
    {
        let mut current_obj_ref = &(*fs.try_borrow().unwrap()).child_dirs;

        for n in current_obj_ref.borrow().iter()
        {
            task2_traverse_and_accumulate_size(n);
        }
    }
}


fn task2()
{
    let mut indent:usize = 0;
    let filesystem = MyFs2000 {
        dir_name: String::from("/"),
        sum_files: Cell::new(0),
        child_dirs: RefCell::new(Vec::new()),
        sum_files_recursive: Cell::new(0),
        parent_dir_ref: Option::None,
    };

    let root_fs = Rc::new(RefCell::new(filesystem));
    let mut current_fs = root_fs.clone();
    let payload_str = std::str::from_utf8(PAYLOAD).unwrap();
    let lines = payload_str.split('\n');
    let mut count: i32 = 0;
    for line in lines
    {
        count = count + 1;
        if line == ""
        {
            continue;
        }
        if line == "$ cd .."
        {
            let mut old_dir_name = String::from("");
            {
                old_dir_name = (*current_fs.try_borrow().unwrap()).dir_name.clone();
            }
            indent = indent - 4;
            // $ cd ..
            let old_fs = current_fs.clone();
            let is_next =  (*old_fs.try_borrow().unwrap()).parent_dir_ref.clone();
            if is_next.is_some()
            {
                current_fs = is_next.unwrap();
            }
            else {
                panic!("Failed to navigate up a level");
            }
            {

                let dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
                // println!("{:indent$}{} DIR-Changed OUT {} -> {}", "", count, old_dir_name, dir_name, indent=indent);
            }

        }
        else if line.starts_with("$ cd")
        {
            // $ cd /

            indent = indent + 4;
            let mut tmp = line.split(" ");
            tmp.next();
            tmp.next();
            let dir_name = tmp.next().unwrap().to_string();

            let found_dir = change_dir(dir_name.clone(), current_fs.clone());
            if (found_dir.is_none())
            {
                let current_dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
                panic!("{} not found? at {}", dir_name, current_dir_name);
            }
            else {
                current_fs = found_dir.unwrap();
            }

            {
                let dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
                //println!("{:indent$}{} DIR-Changed IN to {}", "", count, dir_name, indent=indent);
            }
        }
        else if line == "$ ls"
        {
            // $ ls
        }
        else if line.starts_with("dir")
        {
            let current_dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
            // dir e
            let mut tmp = line.split(" ");
            tmp.next();
            let dir_name = tmp.next().unwrap().to_string();
            //println!("{:indent$}Adding {}", "", &dir_name, indent=indent);
            let new_data = Rc::new(RefCell::new(MyFs2000::new(dir_name.clone(), current_fs.clone())));
            let xx = &(*current_fs.try_borrow().unwrap()).child_dirs;
            let _ = &(*xx.try_borrow_mut().unwrap()).push(new_data.clone());
            //println!("{:indent$}{} adding {} to {}", "", count, dir_name, current_dir_name, indent=indent);
        }
        else
        {
            // 4060174 j
            //calculate on current
            let mut tmp = line.split(" ");
            let val = tmp.next().unwrap().to_string();
            //println!("{}", val);
            let size = val.parse::<i64>().unwrap();
            let dir_name = &(*current_fs.try_borrow().unwrap()).dir_name;
            //println!("{:indent$}adding size: {} to {}", "", size, dir_name, indent=indent);
            let currentsize = &(*current_fs.try_borrow().unwrap()).sum_files.get();
            let _ = &(*current_fs.try_borrow().unwrap()).sum_files.set(currentsize + size);
            //(*current_fs.as_ptr()).sum_files.set(currentsize + size);
        }
    }
    //let mut megasum: i32 = 0;

    // 70000000
    // 30000000
    //  2216306
    let megasum: Rc<Cell<i32>> = Rc::new(Cell::new(0));
    task2_traverse_and_accumulate_size(&root_fs);
    let root_size = &(*root_fs.try_borrow().unwrap()).sum_files_recursive.get();
    let base_size_left = 70000000 - root_size;
    println!("task2: current_disk_used: {}, data left: {})", root_size, base_size_left);

    let sum = Rc::new(Cell::new(i64::MAX));
    search_for_delete_object(&root_fs, 30000000, base_size_left, sum.clone());
    //let sum = Rc::new(Cell::new(0));
    //acc_folder_lower_then(&root_fs, 100000, sum.clone());

    println!("task2 sum: {}", sum.clone().get());

}

fn main()
{
    task1();
    task2();
}
