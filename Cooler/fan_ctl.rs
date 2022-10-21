use std::fs::File;
use std::env;
use std::io::prelude::*;

fn default_pin() -> u16 {
    23
}

fn main() {
    
    //Collect the args
    let args: Vec<String> = env::args().collect();

    //Get Pin#
    let io_pin:u16 = args[1].parse::<u16>().unwrap();
    let op:char = args[2].parse::<char>().unwrap();

    //TODO validate input

    
    let _io_root = "/student/fbl773/School/PROJECTS/piCool/Cooler/gpio";
    let _io_path = format!("{}",_io_root.to_owned()+&io_pin.to_string());
    println!("PATH: {}",_io_path);

    if op == 'r'{
        get_fan_mode(_io_path);
    } else if op == 'a'{
        set_fan_mode(_io_path,1);
    } else if op == 'd'{
        set_fan_mode(_io_path,0);
    } else {
        panic!("UNRECOGNIZED OPERATION: {}",op);
    }

}
/**
 * set_fan
 * @description: Sets a fan to the provided status
 * @param pin: a function that returns the pin the fan runs on
 * @param status: 0 if turning fan on, 1 if turning fan off
 */
fn set_fan_mode(file_path:String, status:u8) -> u8{

    let mut gpio_file = match File::create(&file_path){
        Err(why) => panic!("Failed to open file gpio {}: {}", file_path, why),
        Ok(gpio_file) => gpio_file,
    };

    if status != 1 && status != 0{
        println!("ERROR! Option {status} not recognized!");
        return 1
    }

    let write_me = format!("{}",status);
    match gpio_file.write_all(write_me.as_bytes()){
        Err(why) => panic!("Failed to write {} to path: {} : {}",status,file_path,why),
        Ok(_) => (),
    }

    return 0;
}

fn get_fan_mode(file_path:String) -> u8{

    let mut gpio_file = match File::create(&file_path){
        Err(why) => panic!("Failed to open file gpio {}: {}",file_path , why),
        Ok(gpio_file) => gpio_file,
    };

    let mut status = String::new();
    match gpio_file.read_to_string(&mut status){
        Err(why) => panic!("Failed to read gpio file {} !: {}",file_path,why),
        Ok(_) => println!("Fan Status reported as: {}",status),
    }
    println!("STATUS IS: {}",status);
    //if status != 1 && status != 0{

    return 0;
}





