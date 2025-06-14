#include <system_information_gather.c>

Token get_normal_token(int column,int line,char character[100]){
    
    int i;
    int lenght = len(keywordLookup);
    int character_lenght = len(character);
    for (i=0;i <= lenght; i++);{
        if (strcmp(character,keywordLookup[i].character) == 0){
            Token current_token  = keywordLookup[i].token;
            current_token.column = column;
            current_token.line   = line;
            return current_token;

        }
    }
    if (isdigit(character[0])==0){
        int identifier_counter = identifier_counter + 1;
        if(check_for_int_value(character,character_lenght)==0){
            int value = get_int_value(character);
        }
        else if(check_for_float_value(character,character_lenght)==0){
            int value = get_float_value(character);
        }
        else{

        }
        
    }
    else{
        identifier_counter = identifier_counter + 1;
        //Token current_token  = {.value={.Identifier={.ID=identifier_counter,.type={}}}};
    }
   
 }

bool check_for_int_value(char character[100],int character_lenght){
    int i;
    for (i=0;i<=character_lenght;i++){
        if (isdigit(character[i])==0){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

bool check_for_float_value(char character[100],int character_lenght){
    int i;
    int flag =0;
    for (i=0;i<=character_lenght;i++){
        if (character[i]=="."){
            flag = flag+1;
        }
        if (isdigit(character[i])==0 || flag <=1){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

int get_int_value(char character[100]){
    char *endptr;
    long int_val = strtol(character, &endptr, 10);
        return int_val;
}
double get_float_value(char character[100]){
    char *endptr;
    double float_val = strtod(character, &endptr);
        return float_val;
}