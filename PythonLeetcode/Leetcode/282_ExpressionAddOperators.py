"""
282. Expression Add Operators

Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Example 1:

Input: num = "123", target = 6
Output: ["1+2+3", "1*2*3"]
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2", "2+3*2"]
Example 3:

Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Example 4:

Input: num = "00", target = 0
Output: ["0+0", "0-0", "0*0"]
Example 5:

Input: num = "3456237490", target = 9191
Output: []


Constraints:

0 <= num.length <= 10
num only contain digits.


"""

class AddOperators:

    def doit_back_tracking(self, num: 'str', target: 'int') -> 'List[str]':

        N = len(num)
        answers = []

        def recurse(index, prev_operand, current_operand, value, string):
            # Done processing all the digits in num
            if index == N:

                # If the final value == target expected AND
                # no operand is left unprocessed
                if value == target and current_operand == 0:
                    answers.append("".join(string[1:]))
                return

            # Extending the current operand by one digit
            current_operand = current_operand*10 + int(num[index])
            str_op = str(current_operand)

            # To avoid cases where we have 1 + 05 or 1 * 05 since 05 won't be a
            # valid operand. Hence this check
            if current_operand > 0:

                # NO OP recursion
                recurse(index + 1, prev_operand, current_operand, value, string)

            # ADDITION
            string.append('+'); string.append(str_op)
            recurse(index + 1, current_operand, 0, value + current_operand, string)
            string.pop();string.pop()

            # Can subtract or multiply only if there are some previous operands
            if string:

                # SUBTRACTION
                string.append('-'); string.append(str_op)
                recurse(index + 1, -current_operand, 0, value - current_operand, string)
                string.pop();string.pop()

                # MULTIPLICATION
                string.append('*'); string.append(str_op)
                recurse(index + 1, current_operand * prev_operand, 0, value - prev_operand + (current_operand * prev_operand), string)
                string.pop();string.pop()

        recurse(0, 0, 0, 0, [])
        return answers

    def doit_(self, num, target):
        """
        :type num: str
        :type target: int
        :rtype: List[str]
        """

        def calculate(res, num, pos, path, last, cur, target):

            if pos == len(num):
                if cur == target:
                    res.append(path)
                return

            for i in range(1, len(num) - pos + 1):
                tmp = num[pos: pos + i]
                step = int(tmp)

                if len(tmp) > 1 and tmp[0] == '0':
                    break

                if path:
                    calculate(res, num, pos + i, path + '+' + tmp, step, cur + step, target)

                    calculate(res, num, pos + i, path + '-' + tmp, -step, cur - step, target)

                    calculate(res, num, pos + i, path + '*' + tmp, last * step, (cur - last) + (last * step), target)
                else:
                    calculate(res, num, pos + i, tmp, step, step, target)

        res = []
        calculate(res, num, 0, "", 0, 0, target)
        return res


    def doit_dfs(self, num, target):
        """
        :type num: str
        :type target: int
        :rtype: List[str]
        """
        def dfs(num, start, curSum, prevNum, path):

            if start == len(num):
                if curSum == self.target:
                    self.res.append(path)
                return

            if max(1, abs(prevNum)) * int(num[start:]) < abs(self.target - curSum):
                return

            for i in range(start + 1, len(num) + 1):
                n = num[start:i]
                if i - start > 1 and n[0] == '0':
                    continue
                nInt = int(n)
                if start == 0:
                    dfs(num, i, nInt, nInt, n)
                else:
                    dfs(num, i, curSum + nInt, nInt, path + '+' + n)
                    dfs(num, i, curSum - nInt, -nInt, path + '-' + n)
                    dfs(num, i, curSum - prevNum + prevNum * nInt, prevNum * nInt, path + '*' + n)

        res = []
        target = target
        dfs(num, 0,0,0,'')
        return res

    # Best one
    def addOperators(self, num, target):
        """
        :type num: str
        :type target: int
        :rtype: List[str]
        """

        def r(start, runningVal, prevOp, listString):
            if start == end:
                if runningVal == target:
                    listAnswer.append(listString)
                return

            '''
            THIS single "if" statement below is the optimizer -> UNDERSTAND IT

            Before each recursion cycle -> do this check below:
                -> if what was found * remaining values from num will be greater than or equal to target
                -> then this cycle is worth checking, otherwise traversing down this path is worthless
                -> since the remainder of that path won't have enough to form the target number
            '''
            if max(1, abs(prevOp)) * int(num[start:]) < abs(target - runningVal):
                return

            for index in range(start + 1, end + 1):
                toEvalNumString = num[start:index]
                if index - start > 1 and toEvalNumString[0] == "0":
                    continue
                toEvalNumInt = int(toEvalNumString)
                '''
                REMEMBER -> the new starting index for the next recursion will be:
                         -> "index" from the for range loop, NOT original startIndex
                "i" for a parameter name is not good - easily confused with loop indexes
                '''
                if start == 0:
                    r(index, toEvalNumInt, toEvalNumInt, toEvalNumString)
                else:
                    r(index, runningVal + toEvalNumInt, toEvalNumInt, listString + "+" + toEvalNumString)
                    r(index, runningVal - toEvalNumInt, -toEvalNumInt, listString + "-" + toEvalNumString)
                    r(index, runningVal - prevOp + (prevOp * toEvalNumInt), prevOp * toEvalNumInt, listString + "*" + toEvalNumString)

        listAnswer = []
        target = target
        end = len(num)
        r(0, 0, 0, "")
        return listAnswer

