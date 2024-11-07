#include <stdlib.h>

int fizz(int a) {
	int MODE = 0; // 0 for zero, 1 for fizz, 2 for buzz, 3 for fizzbuzz

    if (a % 3 == 0) {
     MODE = MODE | 1;  
    }

    if (a % 5 == 0) {
     MODE = MODE | 2;
    }

	return MODE;
}

char sprintf_success(int check, int bufflen) {
    return check >= 0 && check < bufflen;
}

void fizz_char_b(char buff[], int bufflen, int upto) {
   for (int i = 1; i <= upto; i++) {
        int check = 0;
        int fizz_mode = fizz(i);
        if (fizz_mode == 0) {
            check = snprintf(buff, bufflen, "%d, ", i);
        } else if (fizz_mode == 1) {
            check = snprintf(buff, bufflen, "Fizz, ");
        } else if (fizz_mode == 2) {
            check = snprintf(buff, bufflen, "Buzz, ");
        } else if (fizz_mode == 3) {
            check = snprintf(buff, bufflen, "Fizzbuzz, ");
        }

        if (!sprintf_success(check, bufflen)) return;

        buff += check;
        bufflen -= check;
   }

   buff -= 2;
   bufflen -= 2;

   snprintf(buff, bufflen, ".");
}


int make_fizz_str(char buff[], int bufflen, int num) {
     int check = 0;
     int fizz_mode = fizz(num);
     if (fizz_mode == 0) {
            check = snprintf(buff, bufflen, "%d", num);
     } else if (fizz_mode == 1) {
            check = snprintf(buff, bufflen, "Fizz");
     } else if (fizz_mode == 2) {
            check = snprintf(buff, bufflen, "Buzz");
     } else if (fizz_mode == 3) {
            check = snprintf(buff, bufflen, "Fizzbuzz");
     }

     return check;
}

void fizz_arr_with_b(char buff[], int bufflen, int nums[], int num_lens) {
    for(int i = 0; i < num_lens; i++) {
       char fizz_str_buff[9] = {0}; 
       int fizz_str_buff_len = 9;
       int fizz_str_check = make_fizz_str(fizz_str_buff, fizz_str_buff_len, nums[i]);
       int check = snprintf(buff, bufflen, "%s, ", fizz_str_buff);


       buff += check;
       bufflen -= check;

       if (!sprintf_success(check, bufflen)) return;    
    }

    buff -= 2;
    bufflen -= 2;

    snprintf(buff, bufflen, ".");
}

char *fizz_arr_with_p(int nums[], int num_len) {
   char *res = "hey"; 

   // at first we calculate final size of the our string
   int total_size = 1;

   for (int i = 0; i < num_len; i++) {
      int size = 1;
      int fizz_mode = fizz(i);

      if (fizz_mode == 0) {
        size += snprintf(NULL, 0, "%d", nums[i]);
      } else if (fizz_mode == 1 || fizz_mode == 2) {
        size += 4; 
      } else {
        size += 8;
      }

      // add dot at the end
      if (i + 1 == num_len) {
        size += 1;
      } else { // adding comma
        size += 2; // ', '
      }
      
      total_size += size;
   }
    
    printf("total size: %d\n", total_size);

    char *final = malloc(total_size * sizeof(char));
    int total_check = 0;
    for (int i = 0; i < num_len; i++) {
       char fizz_str_buff[9] = {0}; 
       int fizz_str_buff_len = 9;
       int fizz_str_check = make_fizz_str(fizz_str_buff, fizz_str_buff_len, nums[i]);
       int check = 0;
       if (i + 1 == num_len) {
         check = sprintf(final, "%s.", fizz_str_buff); 
       } else {
         check = sprintf(final, "%s, ", fizz_str_buff);
       }

       printf("final: %s\tcheck: %d\tfizz: %s\n", final, check, fizz_str_buff);

       final += check;
       total_check += check;
    } 
   printf("check: %d\tsize: %d\t\n", total_check, total_size);

   final -= total_check;

   char me[20000000] = {0};


   sprintf(final, "%s", me);

   return final;
}
