'use strict'


class Itinerary_Reconstruct {

    constructor(arr) {

        this._portArr = [];
        this._route = [];
    
        // make a Graphic of the route
        for (var i = 0; i < arr.length; i++) {
            var from = arr[i].from;
            var end = arr[i].end;
            var fromPos = -1;
            var endPos = -1;
        
            for (var j = 0; j < this._portArr.length; j++) {
                if (this._portArr[j] === from)
                    fromPos = j;
                
                if (this._portArr[j] === end)
                    endPos = j;
            }
            if (fromPos == -1) {
                this._portArr.push(from);
                fromPos = this._portArry.length - 1;
            }
            if (endPos == -1) {
                this._portArr.push(end);
                endPos = this._portArry.length - 1;
            }

            this._route[fromPos].push(endPos); 
        }
    }

    make_itinerary() {



    }  
    

}









function main() {


}

exports.main = main;
