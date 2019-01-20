package leetcodeH

/*

722. Remove Comments

*/

func removeComments(source []string) []string {

	res := make([]string, 0)
	non_blocked := true
	buff := ""

	for _, s := range source {

		for i := 0; i < len(s); i++ {

			if s[i] == '/' && i+1 < len(s) && s[i+1] == '/' && non_blocked {
				break
			} else if s[i] == '/' && i+1 < len(s) && s[i+1] == '*' && non_blocked {
				non_blocked = false
				i++
			} else if s[i] == '*' && i+1 < len(s) && s[i+1] == '/' && !non_blocked {
				non_blocked = true
				i++
			} else if non_blocked {
				buff += string(s[i])
			}
		}

		if len(buff) > 0 && non_blocked {
			res = append(res, buff)
			buff = ""
		}
	}

	return res
}
