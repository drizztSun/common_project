'use strict'

class BackPackIssue {

    static way(arr, C) {    
            
        for (let i = 0; i < arr.length; i++) {
            arr[i].c = arr[i].value / arr[i].V;
        }
    
        let sortByCArray = [];
        for (let i = 0; i < arr.length; i++) {
            sortByCArray.push(arr[i]);
            for (let j = sortByCArray.length - 2; j >= 0; j--) {
                if (arr[i].c > sortByCArray[j].c) {
                    sortByCArray[j + 1] = sortByCArray[j];
                } else {
                    sortByCArray[j + 1] = arr[i];
                    break;
                }
            }
        }

        //
        let Total = 0;
        let i = 0;
        let A = [];
        while (i < sortByCArray.length && Total < C){
            Total += sortByCArray[i].V;
            if (Total == C) {
            A.push(sortByCArray[i]);
                continue;
            } else if (Total > C) {
                Total -= sortByCArray[i].V;
                i--;
                break;
            }
            A.push(sortByCArray[i]); 
            i++;
        }

        return {TotalWeigth : Total, group : A};
    }
}


class Graphic {

    constructor(array) {
        this._node = array;
        this._edge = []
    }

    putEdgeInfo(i, array) {
        this._edge[i] = array;
    }


}

class Tree {
    constructor() {
        this._node = [];
        this._edge = [];
    }

    putEdugeInfo(a, b, edge) {

    }
}


class Shortest_Route{

    static way(G, Pass) {
    
        // Initialize those value;
        let X = [];
        let Y = [];
        let D = [];
        let S = Pass.s;
        let E = Pass.e;

        for (let i = 0; i < G._node.length; i++) {
            X[i] = 0;
            Y[i] = 1;
            D[i] = -1;
        }

        X[S] = 1; Y[S] = 0; D[S] = 0; 
    
        for (let i = 0; i < G._edge[S].length; i++) {
            D[G._edge[S][i].n] = G._edge[S][i].E;
        }
    
        
        let done = false;
        let Path = [];
        Path.push(S);
    
        let isYEmpty = function () {
            for (let i = 1; i < Y.length; i++) {
                if (Y[i] == 1)
                    return false;
            }
            return true;
        }

        while (!isYEmpty(Y)) {
            let min = 10000000000;
            let minPos = 0;
            for (let i = 0; i < Y.length; i++) {
                if (Y[i] == 1 && D[i] > 0 && D[i] < min) {
                    min = D[i];
                    minPos = i;
                }
            }

            X[minPos] = 1; Y[minPos] = 0;
            
            for (let i = 0; i < G._edge[minPos].length; i++) {
                if (D[G._edge[minPos][i].n] == -1 || D[G._edge[minPos][i].n] > G._edge[minPos][i].E + D[minPos]) {
                    D[G._edge[minPos][i].n] = G._edge[minPos][i].E + D[minPos];
                }
            }
        
            if (!done) {
                Path.push(minPos);
                if (minPos == E) done = true;
            }
        }

        return { Dist: D[E], Route: Path };
    }
}

class Smallest_cost_Tree{

    static way_Prim(G) {

        let Tree = [];
        let SC_Tree = new Graphic(G._node);
        let X = [];
        let Y = [];

        for (let i = 0; i < G._node.length; i++) {
            X[i] = 0;
            Y[i] = 1;
        }

        X[1] = 1; Y[1] = 0;
    
        let isYEmpty = function () {
            for (let i = 1; i < Y.length; i++) {
                if (Y[i] == 1)
                    return false;
            }
            return true;
        }

        while (!isYEmpty(Y)) {
            let minEdge = { s: 0, e: 0, min: 100000 };
        
            // check m times, because the amount of edges is m
            for (let i = 1; i < G._edge.length; i++) {
                for (let j = 0; j < G._edge[i].length; j++) {
                    if (G._edge[i][j].E < minEdge.min && X[i] == 1 && Y[G._edge[i][j].n] == 1 ) {
                        minEdge.min = G._edge[i][j].E;
                        minEdge.s = i;
                        minEdge.e = G._edge[i][j].n;
                    }
                }   
            }

            X[minEdge.e] = 1;
            Y[minEdge.e] = 0;
            if (SC_Tree._edge[minEdge.s] == undefined)
                SC_Tree._edge[minEdge.s] = [];
            SC_Tree._edge[minEdge.s].push({n: minEdge.e, E: minEdge.min});
        }
    
        return SC_Tree;
    }

    static way_Krushal(G) {

    }

}


function main() {

    let A = [
        {value : 3, V : 2}, 
        {value : 4, V : 3},
        {value : 5, V : 4},
        {value : 7, V : 5}//,
        //{value : , V :},
        //{value : , V :},
        //{value : , V :}
    ];
    
    let B = BackPackIssue.way(A, 9);
    console.log("The best group is :  " + B.Total + " Groups is " + B.group);


    // shorest route distance
    let a = [0, 1, 2, 3, 4, 5, 6];
    let g = new Graphic(a);
    g.putEdgeInfo(0, []);
    g.putEdgeInfo(1, [{ n: 2, E: 1 }, { n: 3, E: 12 }]);
    g.putEdgeInfo(2, [{ n: 4, E: 3 }, { n: 3, E: 9 }]);
    g.putEdgeInfo(3, [{ n: 5, E: 5 }]);
    g.putEdgeInfo(4, [{ n: 3, E: 4 }, { n: 5, E: 13 }, { n: 6, E: 15 }]);
    g.putEdgeInfo(5, [{ n: 6, E: 4 }]);
    g.putEdgeInfo(6, []);
    let res = Shortest_Route.way(g, { s: 1, e: 6 });
    console.log("The shortest distance is " + res.Dist + " Path : " + res.Route);
    
    let double_g = new Graphic(a);
    double_g.putEdgeInfo(0, []);
    double_g.putEdgeInfo(1, [{ n: 2, E: 1 }, { n: 3, E: 2 }]);
    double_g.putEdgeInfo(2, [{ n: 4, E: 11 }, { n: 3, E: 6 }, {n: 1, E: 1}]);
    double_g.putEdgeInfo(3, [{ n: 5, E: 13 }, { n: 1, E: 2 }, { n: 2, E: 6 }, { n: 4, E: 9 }]);
    double_g.putEdgeInfo(4, [{ n: 3, E: 9 }, { n: 5, E: 7 }, { n: 2, E: 11 }, { n : 6, E: 3 }]);
    double_g.putEdgeInfo(5, [{ n: 6, E: 4 }, { n: 4, E: 7}, { n: 3, E:13}]);
    double_g.putEdgeInfo(6, [{ n: 5, E:4}, { n: 4, E: 3}]);
    
    let res_tree = Smallest_cost_Tree.way_Prim(double_g);
    
    console.log("The smallest cost tree is " + res_tree);   

}

exports.main = main;