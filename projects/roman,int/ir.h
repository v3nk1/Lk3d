int roman2int(char ch){

        switch(ch){

                case 'M':
                        return 1000;
                case 'D':
                        return 500;
                case 'C':
                        return 100;
                case 'L':
                        return 50;
                case 'X':
                        return 10;
                case 'V':
                        return 5;
                case 'I':
                        return 1;
                default:
                        return 0;
	}
}

char *int2roman(int in){

	switch(in){

		case 1:
			return "I";
		case 4:
			return "IV";
		case 5:
			return "V";
		case 9:
			return "IX";
		case 10:
			return "X";
		case 40:
			return "XL";
		case 50:
			return "L";
		case 90:
			return "XC";
		case 100:
			return "C";
		case 400:
			return "CD";
		case 500:
			return "D";
		case 900:
			return "CM";
		case 1000:
			return "M";
		default:
			return "";

	}

}
