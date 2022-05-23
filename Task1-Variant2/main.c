#include <stdio.h>
#include <stdlib.h>
#define DefaultSetLength 10

int CommandRecognition(char* string) {
	int i = 0;
	char append[] = "append";
	char del[] = "delete";
	char del_all[] = "deleteall";
	char convert[] = "convert";
	char exit[] = "exit";
	char show[] = "show";
	int append_flag = 1;
	int append_binary_flag = 1;
	int del_flag = 1;
	int del_all_flag = 1;
	int convert_flag = 1;
	int exit_flag = 1;
	int show_flag = 1;
	char l;
	while ((l = string[i]) != '\0') {
		if (l >= 'A' && l <= 'Z') l = l - 'A' + 'a';
		if (l != append[i]) append_flag = 0;
		if (l != del[i]) del_flag = 0;
		if (l != del_all[i]) del_all_flag = 0;
		if (l != convert[i]) convert_flag = 0;
		if (l != exit[i]) exit_flag = 0;
		if (l != show[i]) show_flag = 0;
		i++;
	}
	if (append_flag) return 1; // command - append
	if (del_flag) return 2; // command - delete
	if (convert_flag) return 3; // comand - convert
	if (exit_flag) return 4; // command - exit
	if (show_flag) return 5; // command - show set
	if (del_all_flag) return 6; // command - delete all
	return 0; // ERROR: command unrecognized
}

struct Set {
	int *array;
	int array_length;
	int set_length;
	short is_sorted;
};

void InitializeSet(struct Set* set) {
	int* set_array = (int*)calloc(DefaultSetLength, sizeof(int));
	set->array = set_array;
	set->array_length = DefaultSetLength;
	set->set_length = 0;
	set->is_sorted = 1;
}

void QuickSort (int *array, int begin, int end) {
	int base_index = (begin + end) / 2;
	int base = array[base_index];
	for (int i = 0; i < base_index; i++) {
		if (array[i] > base) {
			int x = array[i];
			for (int j = i; j <= base_index; j++)
				array[j] = array[j + 1];
			array[base_index] = x;
			base_index--;
			i--;
		}
	}

	for (int i = base_index+1; i <= end; i++) {
		if (array[i] < base) {
			int x = array[i];
			for (int j = i; j >= base_index; j--)
				array[j] = array[j - 1];
			array[base_index] = x;
			base_index++;
		}
	}
	if (end - begin> 1) {
		QuickSort(array, begin, base_index);
		QuickSort(array, base_index , end);
	}
}

void ShowSet(struct Set set) {
	if (set.set_length == 0) puts("Set is empty");
	else {
		int length = set.set_length;
		for (int i = 0; i < length; i++) {
			printf("%d ", set.array[i]);
		}
		putchar('\n');
	}
}

void Append(struct Set* set, int number) {
	int setlength = set->set_length;
	for (int i = 0; i < setlength; i++) if (number == set->array[i]) return;
	set->is_sorted = 0;
	set->array[setlength] = number;
	setlength = ++set->set_length;
	
	if (setlength == set->array_length) {
		int* new_array = (int*)calloc(setlength+ DefaultSetLength, sizeof(int));
		for (int i = 0; i < setlength; i++) new_array[i] = set->array[i];
		free(set->array);
		set->array = new_array;
		set->array_length += DefaultSetLength;
	}
}

void Delete(struct Set* set, int number) {
	int setlength = set->set_length;
	for (int position = 0; position < setlength; position++) {
		if (set->array[position] == number) {
			for (int i = position; i < setlength - 1; i++) {
				set->array[i] = set->array[i + 1];
			}
			set->set_length--;
			return; // Sucsesfully deleted
		}
	}
	return; // Where are no such element in set
}

void DeleteAll(struct Set* set) {
	free(set->array);
	set->array = (int*)calloc(DefaultSetLength, sizeof(int));
	set->is_sorted = 1;
	set->set_length = 0;
	set->array_length = DefaultSetLength;
}

void ConvertSetToBinary(struct Set decimal_set) {
	int setlength = decimal_set.set_length;
	if (setlength == 0) {
		puts("Set is empty. Nothing to convert.");
		return;
	}
	int element, x;
	for (int i = 0; i < setlength; i++) {
		element = decimal_set.array[i];
		printf("Decimal %d = ", element);
		x = 1;
		if (element < 0) {
			putchar('-');
			element *= -1;
		}
		if (element == 0) {
			puts("0 binary");
			continue;
		}
		while (x <= element) x *= 2;
		x /= 2;
		while (x > 0) {
			if (x & element) putchar('1');
			else putchar('0');
			x /= 2;
		}
		printf(" binary\n");
	}
}

int main() {
	puts("This is task 1, variant 2\n"
		"It had benn made by Karyshev Boris from IU4-21B\n"
		"List of commands:\n"
		"\tShow - show all elements of set\n"
		"\tAppend - add new elements (1 or more) in set. (Ex: append 1 2 3 4 - elements 1 2 3 4 will be added in set)\n"
		"\tDelete - delete 1 or more elements from set. (similar to append)\n"
		"\tConvert - converts all elements of set from decimal form into binary\n"
		"\tDeleteAll - deleting all values from set\n"
		"\tExit - terminates the application\n"
		"When entering commands, case doesn't matter\n"
	);
	struct Set decimal_numbers;
	InitializeSet(&decimal_numbers);

	char command_string[100];
	int argument;
	while (scanf("%s", command_string)) {
		switch (CommandRecognition(command_string)) {
		case 0:
			printf("\nCommand unrecognized. Please try again.\n");
			break;
		case 1:
			while (scanf("%d\n", &argument)) Append(&decimal_numbers, argument);
			break;
		case 2:
			while (scanf("%d\n", &argument)) Delete(&decimal_numbers, argument);
			break;
		case 3:
			if (!decimal_numbers.is_sorted) {
				QuickSort(decimal_numbers.array, 0, decimal_numbers.set_length - 1);
				decimal_numbers.is_sorted = 1;
			}
			ConvertSetToBinary(decimal_numbers);
			break;
		case 4:
			return 0;
		case 5:
			if (!decimal_numbers.is_sorted) {
				QuickSort(decimal_numbers.array, 0, decimal_numbers.set_length - 1);
				decimal_numbers.is_sorted = 1;
			}
			ShowSet(decimal_numbers);
			break;
		case 6:
			DeleteAll(&decimal_numbers);
			break;
		}
	}
}