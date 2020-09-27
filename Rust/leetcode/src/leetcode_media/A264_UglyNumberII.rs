use std::cmp::min;

struct Nthuglynumber (u8);

impl Nthuglynumber {
    pub fn doit_array(n: i32) -> i32 {
        
        let mut buf = vec![1];
        let mut i2 = 0;
        let mut i3 = 0;
        let mut i5 = 0;
        
        
        while buf.len() < n as usize {
            
            let a2 = buf[i2] * 2;
            let a3 = buf[i3] * 3;
            let a5 = buf[i5] * 5;
            
            let minor = min(a2, min(a3, a5));
            
            if minor == a2 {
                i2+=1;
            }

            if minor == a3 {
                i3+=1;
            }

            if minor == a5 {
                i5+=1;
            }
            buf.push(minor);
        }
        println!("{}", buf.len());
        return buf[buf.len()-1];
    }
}

pub fn test_264_UglyNumberII() {

    Nthuglynumber::doit_array(10);
}