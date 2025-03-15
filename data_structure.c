#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 100
#define TABLE_SIZE 50

typedef struct {
    float percentile;
    char* city_of_origin;
    short int attempt;
} Data;

typedef struct person {
    char name[MAX_NAME];
    short age;
    Data data;

    struct person* next;
    struct person* prev;
} person;

person* hash_table[TABLE_SIZE];

// Hash function can be different and made better
unsigned int hash(char* name, int age) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
 
    hash_value = (age * length + name[age % length]) % TABLE_SIZE;

    return hash_value;
}

person void_person() {
    return (person) {
        .name = "", 
        .age = -1, 
        (Data) {
            .percentile = 0.0, 
            .city_of_origin = "", 
            .attempt = -1
        }
    };
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++)
    hash_table[i] = NULL;
    return;
}

void print_table() {
    printf("Start\n\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) 
        printf("%02i : ---\n", i);

        else {
            printf("%02i : ", i);
            person* current = hash_table[i];
            while (current != NULL) {
                printf("%s | %d -> ", current->name, current->age);
                current = current->next;
            }
            printf("NULL\n");
        }
    }

    printf("\nEnd\n\n\n");
    return;
}

bool hash_table_insert(person* p) {
    if (p == NULL) return false;
    int index = hash(p->name, p->age);

    if (hash_table[index] == NULL) {
        hash_table[index] = p;
        p->next = NULL;
        p->prev = NULL;

    } else {
        person* current = hash_table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = p;
        p->prev = current;
        p->next = NULL;
    }
    return true;
}

person hash_table_lookup(char* name, int age) {
    unsigned int index = hash(name, age);
    person* current = hash_table[index];

    while (current != NULL) {
        if (strncmp(current->name, name, MAX_NAME) == 0 
        && current->age == age) 
        return *current;

        current = current->next;
    }
    return void_person();
}

person hash_table_delete(char* name, int age) {
    int index = hash(name, age);
    person* current = hash_table[index];

    while (current != NULL) {
        if (strncmp(current->name, name, MAX_NAME) == 0 
        && current->age == age) 
        {
            if (current->prev != NULL)
            current->prev->next = current->next;
            else
            hash_table[index] = current->next;

            if (current->next != NULL)
            current->next->prev = current->prev;
        
            return *current;
        }
        current = current->next;
    }
    return void_person();
}

int main(void) {
    person p;
    
    init_hash_table();

    person people[] = {
        {"Alice", 25, {90.5, "New York", 1}}, {"Bob", 30, {85.0, "Los Angeles", 2}}, {"Charlie", 22, {88.0, "Chicago", 1}}, 
        {"David", 45, {92.0, "Houston", 3}}, {"Eve", 35, {87.5, "Phoenix", 2}}, {"Frank", 28, {89.0, "Philadelphia", 1}}, 
        {"Grace", 33, {91.0, "San Antonio", 2}}, {"Hank", 40, {86.5, "San Diego", 3}}, {"Ivy", 29, {90.0, "Dallas", 1}}, 
        {"Jack", 31, {88.5, "San Jose", 2}}, {"Kathy", 27, {89.5, "Austin", 1}}, {"Leo", 34, {87.0, "Jacksonville", 2}}, 
        {"Mona", 26, {91.5, "Fort Worth", 1}}, {"Nina", 32, {90.0, "Columbus", 2}}, {"Oscar", 23, {88.0, "Charlotte", 1}}, 
        {"Paul", 36, {92.5, "San Francisco", 3}}, {"Quinn", 37, {85.5, "Indianapolis", 2}}, {"Rita", 38, {89.0, "Seattle", 1}}, 
        {"Sam", 39, {91.0, "Denver", 2}}, {"Tina", 41, {87.5, "Washington", 3}}, {"Uma", 42, {90.5, "Boston", 1}}, 
        {"Vince", 43, {88.0, "El Paso", 2}}, {"Wendy", 44, {89.5, "Detroit", 1}}, {"Xander", 46, {91.0, "Nashville", 2}}, 
        {"Yara", 47, {87.0, "Memphis", 1}}, {"Zane", 48, {90.0, "Portland", 2}}, {"Amy", 49, {88.5, "Oklahoma City", 1}}, 
        {"Brian", 50, {89.0, "Las Vegas", 2}}, {"Cathy", 51, {91.5, "Louisville", 1}}, {"Derek", 52, {87.5, "Baltimore", 2}}, 
        {"Ella", 53, {90.0, "Milwaukee", 1}}, {"Fred", 54, {88.0, "Albuquerque", 2}}, {"Gina", 55, {89.5, "Tucson", 1}}, 
        {"Holly", 56, {91.0, "Fresno", 2}}, {"Ian", 57, {87.0, "Sacramento", 1}}, {"Jane", 58, {90.5, "Mesa", 2}}, 
        {"Kyle", 59, {88.5, "Kansas City", 1}}, {"Lara", 60, {89.0, "Atlanta", 2}}, {"Mike", 61, {91.5, "Omaha", 1}}, 
        {"Nora", 62, {87.5, "Raleigh", 2}}, {"Owen", 63, {90.0, "Miami", 1}}, {"Pam", 64, {88.0, "Long Beach", 2}}, 
        {"Quincy", 65, {89.5, "Virginia Beach", 1}}, {"Ralph", 66, {91.0, "Oakland", 2}}, {"Sara", 67, {87.0, "Minneapolis", 1}}, 
        {"Tom", 68, {90.5, "Tulsa", 2}}, {"Ursula", 69, {88.5, "Arlington", 1}}, {"Victor", 70, {89.0, "New Orleans", 2}}, 
        {"Wade", 71, {91.5, "Wichita", 1}}, {"Xena", 72, {87.5, "Cleveland", 2}}, {"Yvonne", 73, {90.0, "Tampa", 1}}, 
        {"Zack", 74, {88.0, "Bakersfield", 2}}, {"Anna", 75, {89.5, "Aurora", 1}}, {"Ben", 76, {91.0, "Anaheim", 2}}, 
        {"Cara", 77, {87.0, "Santa Ana", 1}}, {"Dylan", 78, {90.5, "Corpus Christi", 2}}, {"Eva", 79, {88.5, "Riverside", 1}}, 
        {"Finn", 80, {89.0, "Lexington", 2}}, {"Gail", 81, {91.5, "St. Louis", 1}}, {"Hank", 82, {87.5, "Stockton", 2}}, 
        {"Iris", 83, {90.0, "Pittsburgh", 1}}, {"Jake", 84, {88.0, "Saint Paul", 2}}, {"Kara", 85, {89.5, "Cincinnati", 1}}, 
        {"Liam", 86, {91.0, "Anchorage", 2}}, {"Mia", 87, {87.0, "Henderson", 1}}, {"Nate", 88, {90.5, "Greensboro", 2}}, 
        {"Omar", 89, {88.5, "Plano", 1}}, {"Pia", 90, {89.0, "Newark", 2}}, {"Quinn", 91, {91.5, "Lincoln", 1}}, 
        {"Rose", 92, {87.5, "Orlando", 2}}, {"Sean", 93, {90.0, "Irvine", 1}}, {"Tara", 94, {88.0, "Toledo", 2}}, 
        {"Uma", 95, {89.5, "Jersey City", 1}}, {"Vera", 96, {91.0, "Chula Vista", 2}}, {"Will", 97, {87.0, "Fort Wayne", 1}}, 
        {"Xavi", 98, {90.5, "St. Petersburg", 2}}, {"Yuri", 99, {88.5, "Laredo", 1}}, {"Zara", 24, {89.0, "Durham", 2}},
        {"Aaron", 26, {90.0, "Madison", 1}}, {"Bella", 27, {88.0, "Lubbock", 2}}, {"Cody", 28, {89.5, "Chandler", 1}}, 
        {"Diana", 29, {91.0, "Scottsdale", 2}}, {"Ethan", 30, {87.0, "Glendale", 1}}, {"Fiona", 31, {90.5, "Reno", 2}}, 
        {"George", 32, {88.5, "Norfolk", 1}}, {"Hannah", 33, {89.0, "Winston-Salem", 2}}, {"Isaac", 34, {91.5, "North Las Vegas", 1}}, 
        {"Jill", 35, {87.5, "Irving", 2}}, {"Kevin", 36, {90.0, "Chesapeake", 1}}, {"Lily", 37, {88.0, "Gilbert", 2}}, 
        {"Mason", 38, {89.5, "Hialeah", 1}}, {"Nina", 39, {91.0, "Garland", 2}}, {"Oscar", 40, {87.0, "Fremont", 1}}, 
        {"Paula", 41, {90.5, "Richmond", 2}}, {"Quincy", 42, {88.5, "Boise", 1}}, {"Randy", 43, {89.0, "Baton Rouge", 2}}, 
        {"Sophie", 44, {91.5, "Des Moines", 1}}, {"Trent", 45, {87.5, "Spokane", 2}}, {"Ulysses", 46, {90.0, "San Bernardino", 1}}, 
        {"Violet", 47, {88.0, "Modesto", 2}}, {"Wes", 48, {89.5, "Fontana", 1}}, {"Xander", 49, {91.0, "Santa Clarita", 2}}, 
        {"Yasmin", 50, {87.0, "Birmingham", 1}}, {"Zane", 51, {90.5, "Oxnard", 2}}, {"Ava", 52, {88.5, "Fayetteville", 1}}, 
        {"Blake", 53, {89.0, "Moreno Valley", 2}}, {"Chloe", 54, {91.5, "Rochester", 1}}, {"Dylan", 55, {87.5, "Glendale", 2}}, 
        {"Eli", 56, {90.0, "Huntington Beach", 1}}, {"Faith", 57, {88.0, "Salt Lake City", 2}}, {"Gavin", 58, {89.5, "Grand Rapids", 1}}, 
        {"Hazel", 59, {91.0, "Amarillo", 2}}, {"Ian", 60, {87.0, "Yonkers", 1}}, {"Jade", 61, {90.5, "Aurora", 2}}, 
        {"Kyle", 62, {88.5, "Montgomery", 1}}, {"Luna", 63, {89.0, "Akron", 2}}, {"Milo", 64, {91.5, "Little Rock", 1}}, 
        {"Nina", 65, {87.5, "Huntsville", 2}}, {"Owen", 66, {90.0, "Augusta", 1}}, {"Piper", 67, {88.0, "Mobile", 2}}, 
        {"Quinn", 68, {89.5, "Grand Prairie", 1}}, {"Riley", 69, {91.0, "Overland Park", 2}}, {"Seth", 70, {87.0, "Tallahassee", 1}}, 
        {"Tina", 71, {90.5, "Cape Coral", 2}}, {"Umar", 72, {88.5, "Shreveport", 1}}, {"Vera", 73, {89.0, "Frisco", 2}}, 
        {"Wade", 74, {91.5, "Knoxville", 1}}, {"Xena", 75, {87.5, "Worcester", 2}}, {"Yara", 76, {90.0, "Brownsville", 1}}, 
        {"Zane", 77, {88.0, "Vancouver", 2}}, {"Aiden", 78, {89.5, "Fort Lauderdale", 1}}, {"Bella", 79, {91.0, "Sioux Falls", 2}}, 
        {"Cody", 80, {87.0, "Ontario", 1}}, {"Diana", 81, {90.5, "Chattanooga", 2}}, {"Ethan", 82, {88.5, "Providence", 1}}, 
        {"Fiona", 83, {89.0, "Newport News", 2}}, {"George", 84, {91.5, "Rancho Cucamonga", 1}}, {"Hannah", 85, {87.5, "Santa Rosa", 2}}, 
        {"Isaac", 86, {90.0, "Oceanside", 1}}, {"Jill", 87, {88.0, "Salem", 2}}, {"Kevin", 88, {89.5, "Elk Grove", 1}}, 
        {"Lily", 89, {91.0, "Garden Grove", 2}}, {"Mason", 90, {87.0, "Pembroke Pines", 1}}, {"Nina", 91, {90.5, "Peoria", 2}}, 
        {"Oscar", 92, {88.5, "Eugene", 1}}, {"Paula", 93, {89.0, "Corona", 2}}, {"Quincy", 94, {91.5, "Cary", 1}}, 
        {"Randy", 95, {87.5, "Springfield", 2}}, {"Sophie", 96, {90.0, "Fort Collins", 1}}, {"Trent", 97, {88.0, "Jackson", 2}}, 
        {"Ulysses", 98, {89.5, "Alexandria", 1}}, {"Violet", 99, {91.0, "Hayward", 2}}, {"Wes", 100, {87.0, "Clarksville", 1}}
    };

    int size = sizeof(people) / sizeof(people[0]);
    for (int i = 0; i < size; i++) {
        hash_table_insert(&people[i]);
    }

    print_table();

    p = hash_table_lookup("Quincy", 65);

    if (p.age == -1) {
        printf("%s Not found\n", "Quincy");
    }else {
        printf("Name: %s\n", p.name);
        printf("Age: %d\n", p.age);
        printf("Percentile: %.2f\n", p.data.percentile);
        printf("City of Origin: %s\n", p.data.city_of_origin);
        printf("Attempt: %d\n", p.data.attempt);
    }

    return 0;
}
