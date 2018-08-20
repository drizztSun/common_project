'use strict'



class Graphic {
    constructor(array) {
        this._node = array;
        this._edge = []
    }

    putEdgeInfo(i, array) {
        this._edge[i] = array;
    }
}


class Color_N_Graphic{

    static color_is_legal_ornot(G, C) {
        let result = 0;
        let done = false;
        for (let i = 0; !done && i < G._node.length; i++) {
            let a = G._node[i];
            let b = G._edge[a];
        
            if (C[a] == 0)
                continue;

            for (let j = 0; j < b.length; j++) {
                if (C[b[j]] == 0) {
                    result = 1;
                } else if (C[b[j]] == C[a]) {
                    result = -1;
                    done = true;
                    break;
                }
            }
        }
        return result;
    }

    // normal iterate way
    static normal_way(G, N) {

        let C = [];
        for (let i = 0; i <= G._node.length ; i++) {
            C[i] = 0;
        }
    
        let done = false;
        let K = 1;
        while (K >= 1 && !done) {

            while (C[K] <= N - 1) {
                C[K] = C[K] + 1;
                let color = Color_N_Graphic.color_is_legal_ornot(G, C);
                if (color == 1) {
                    K++;
                } else if (color == 0) {
                    done = true;
                    break;
                } else if (color == -1)
                    continue;
            }

            // need back_tracking
            if (!done) {
                C[K] = 0;
                K--;
            }
        }

        return C;
    }

    // recurrecne way
    static recur_way(G, N) {
    
        let done = false;
        let C = [];
        for (let i = 0; i < G._node.length + 1; i++)
            C[i] = 0;

        let iterate_each = function (K) {
            while (C[K] <= N - 1) {
                C[K] = C[K] + 1;
                let res = Color_N_Graphic.color_is_legal_ornot(G, C);           
                if (res == 0) {
                    done = true;
                    return;
                } else if (res == 1){
                    iterate_each(K + 1);
                    if (done)
                        return;
                } else if (res == -1) {
                    continue;
                }
            }
            C[K] = 0;
        }
    
        iterate_each(1);

        return C;
    }
}


class PARTITION_NUMBER {

    constructor(arr, N) {
        this._arr = arr;
        this._sum = N;
        this._C = [];
    }

    static isWorked(arr, C, N) {
        let sum = 0;
        let i = 0;
        for (; i < arr.length && sum <= N; i++) {
            if (C[i] == 1)
                sum += arr[i];
            if (sum > N)
                return -1; 
        }
        
        return sum == N ? 0 : 1;
    }

    static solution(arr, SUM){
        let result = [];
        let C = [];
        for (let i = 0; i < arr.length; i++)
            C[i] = 0;

        let iterator = function(k, sum) {
            //
            if (sum == 0) {
                let B = [];
                for (let i = 0; i < C.length; i++) {
                    if (C[i] == 1)
                        B.push(arr[i]);
                }         
                result.push(B);
                return;
            }

            if (sum < 0 || k >= arr.length)
                return;

            C[k] = 1;
            iterator(k + 1, sum - arr[k]);

            C[k] = 0;
            iterator(k + 1, sum);
        }

        iterator(0, SUM);
        return result;
    }
}




class Queen_N_issue {

    static getPossibleQueenPosition(N) {

        let C = [];
        let done = false;
    
        for (let j = 0; j < N; j++) {
            C[j] = 0;
        }

        let isFullCorrectOrPart = function () {
            let result = 0;
            let done = false;
            for (let i = 0; i < C.length; i++) {
                if (C[i] == 0) {
                    result = 1;
                    continue;
                }
            
                for (let j = i + 1; j < C.length; j++) {
                    if (C[j] != 0 && (C[i] == C[j] || (C[i] - C[j] == i - j)))
                        return -1;
                }
            }
            return result;
        }
    

        let K = 0;
        while (K >= 0 && !done) {
            while (C[K] < N) {
                C[K] = C[K] + 1
                let a = isFullCorrectOrPart();
                if (a == 1) {
                    K++
                    continue;
                } else if (a == 0) {
                    done = true;
                    break;
                } else if (a == -1)
                    continue;
            }

            if (!done) {
                C[K] = 0;
                K--;
            }
        }

        return C;
    }

    static getPossibleQueenPosition_recur(N) {
        
        let C = [];
        for (let i = 0; i < N; i++) {
            C[i] = 0;
        }
    
        // check part/whole/invalid result
        let isFullCorrectOrPart = function () {
            let result = 0;
            let done = false;
            for (let i = 0; i < C.length; i++) {
                if (C[i] == 0) {
                    result = 1;
                    continue;
                }
            
                for (let j = i + 1; j < C.length; j++) {
                    if (C[j] != 0 && (C[i] == C[j] || (C[i] - C[j] == i - j)))
                        return -1;
                }
            }
            return result;
        }

        // 
        let done = false;
        let iterate = function (k) {
            while (C[k] < N) {
                C[k] = C[k] + 1;
                let a = isFullCorrectOrPart();
                if (a == 1) {
                    iterate(k + 1);
                    if (done)
                        return; 
                } else if (a == 0) {
                    done = true;
                    return;
                } else if (a == -1)
                    continue;
            }
            C[k] = 0;
        }
    
        iterate(0);
        return C;
    }

}


/**
 * Leetcode 1 two sum
 * Leetcode 15 three sum 3sum
 * Leetcode 18 four sum 4sum
 * */
class array_to_sum {

    static twoSum(arr, expectedAmount) {
    
        let result = [];
        let C = [];
        for (let i = 0; i < arr.length; i++)
            C.push(0);
    
        let SUM = 0;
    
        let iterate = function (index, sum) {
        
            if (sum == expectedAmount) {
                let B = [];
                for (let i = 0; i < C.length; i++) {
                    if (C[i] == 1)
                        B.push(arr[i]);
                }

                if (B.length == 2) {
                    result.push(B);
                    return;
                } else if (B.length > 2) {
                    return;
                }
            }
        
            if (index == arr.length)
                return;
        
            C[index] = 1;
            iterate(index + 1, sum + arr[index]);
        
            C[index] = 0;
            iterate(index + 1, sum);
        }
    
        C[0] = 1;
        iterate(1, SUM + arr[0]);
    
        C[0] = 0;
        iterate(1, SUM);
    
        return result;
    }


}


function main() {
    
    console.log("-------------------------Start backtracking----------------------------------------")

    let g = new Graphic([1, 2, 3, 4, 5]);
    g.putEdgeInfo(1, [2, 3]);
    g.putEdgeInfo(2, [1, 4, 5]);
    g.putEdgeInfo(3, [1, 4, 5]);
    g.putEdgeInfo(4, [2, 3, 5]);
    g.putEdgeInfo(5, [2, 3, 4]);
    
    let way = Color_N_Graphic.normal_way(g, 3);
    console.log("3 Color solution is " + way);

    let way1 = Color_N_Graphic.recur_way(g, 3);
    console.log("3 Color solution is " + way1);
       
    console.log("Queen is pos " + Queen_N_issue.getPossibleQueenPosition(4));
    console.log("Queen is pos " + Queen_N_issue.getPossibleQueenPosition(5));

    console.log("Queen is pos " + Queen_N_issue.getPossibleQueenPosition_recur(4));
    console.log("Queen is pos " + Queen_N_issue.getPossibleQueenPosition_recur(5));
    
    let input = [10, 20, 30, 40, 50, 60];
    let a = PARTITION_NUMBER.solution(input, 60);
    //let a = PARTITION_NUMBER.solutionLoop(input, 60);
    console.log("[10, 20, 30, 40, 50, 60], The all group equal 60 are : ");
    for (let i = 0; i < a.length; i++) {
        console.log("item " + i + " : " + a[i]);
    }


    console.log("2SUm is " + array_to_sum.twoSum([1, -4, 5, -1, 4, -5], 0))

    console.log("2SUm is " + array_to_sum.twoSum([3, 2, 4], 6))

    console.log("-------------------------End backtracking------------------------------------------")
}

exports.main = main;