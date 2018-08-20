'use strict'


/**
 * China chess issue
 * 
 * uses one vairant and only one, to express "Jiang and Shuai face to face" isse 
 * */
function Jiang_Shuai_face_to_face()
{
    let setHigh = function(a, b) {
        b <<= 4;
        return a & 0x0F | b;
    }

    let getHigh = function (a) {
        a &= 0xF0;
        a >>= 4;
        return a;
    }

    let setLow = function (a, b) {
        return a & 0xF0 | b;
    }

    let getLow = function (a) {
        return a & 0x0F;
    }
    
    console.log("Chess posistion is : ");
    let pos = 0;
    pos = setLow(pos, 1);
    while (getLow(pos) <= 9) {
        pos = setHigh(pos, 1); 
        while (getHigh(pos) <= 9) {
            
            if (getHigh(pos) % 3 != getLow(pos) % 3) {
                console.log("A= " + getHigh(pos) + " B= " + getLow(pos));
            }
            pos = setHigh(pos, getHigh(pos) + 1);
        }
        pos = setLow(pos, getLow(pos) + 1);
    }
    return;
}




function main() {

    Jiang_Shuai_face_to_face();

}


exports.main = main;