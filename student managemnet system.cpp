#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIVISIONS 2

typedef struct student {
  int id;
  char name[50];
  int priority;
  struct student *next;
} Student;

typedef struct subject {
  char subjectName[50];
  int cie;
  int ese;
  char subjectg[5];
} Subject;

typedef struct cstudent {
  int id;
  char name[50];
  char division[10];
  Subject subjects[3];
  struct cstudent *next;  // Corrected the next pointer type to cstudent
} cStudent;

Student *front = NULL;
Student *rear = NULL;
cStudent *head = NULL;

int count = 0;

void enqueue(int id, char *name, int priority) {
  Student *newStudent = (Student *)malloc(sizeof(Student));
  newStudent->id = id;
  strcpy(newStudent->name, name);
  newStudent->priority = priority;
  newStudent->next = NULL;

  if (front == NULL) {
    front = newStudent;
    rear = newStudent;
  } else {
    rear->next = newStudent;
    rear = newStudent;
  }
  count++;
}

void priorityEnqueue(int id, char *name, int priority) {
  Student *newStudent = (Student *)malloc(sizeof(Student));
  newStudent->id = id;
  strcpy(newStudent->name, name);
  newStudent->priority = priority;

  if (front == NULL || priority > front->priority) {
    newStudent->next = front;
    front = newStudent;
  } else {
    Student *temp = front;
    while (temp->next != NULL && temp->next->priority >= priority) {
      temp = temp->next;
    }

    newStudent->next = temp->next;
    temp->next = newStudent;
  }

  count++;
}

void dequeue() {
  if (front == NULL) {
    printf("Queue is empty\n");
    return;
  }

  Student *temp = front;
  front = front->next;
  free(temp);

  count--;
}

void deleteStudent(int id) {
  if (front == NULL) {
    printf("Queue is empty\n");
    return;
  }

  if (front->id == id) {
    dequeue();
    printf("Student with ID %d deleted\n", id);
    return;
  }

  Student *current = front;
  Student *prev = NULL;

  while (current != NULL && current->id != id) {
    prev = current;
    current = current->next;
  }

  if (current == NULL) {
    printf("Student with ID %d not found\n", id);
    return;
  }

  prev->next = current->next;
  free(current);
  count--;
  printf("Student with ID %d deleted\n", id);
}

void confirmAdmission() {
  if (front == NULL) {
    printf("Queue is empty\n");
    return;
  }

  Student *temp = front;

  cStudent *newCStudent = (cStudent *)malloc(sizeof(cStudent));
  newCStudent->id = temp->id;
  strcpy(newCStudent->name, temp->name);

  if (temp->priority > 85) {
    strcpy(newCStudent->division, "A");
  } else if (temp->priority > 70) {
    strcpy(newCStudent->division, "B");
  } else if (temp->priority > 50) {
    strcpy(newCStudent->division, "C");
  } else {
    strcpy(newCStudent->division, "D");
  }

  for (int i = 0; i < 3; i++) {
    strcpy(newCStudent->subjects[i].subjectName, "");
    newCStudent->subjects[i].cie = 0;
    newCStudent->subjects[i].ese = 0;
   strcpy(newCStudent->subjects[i].subjectg, "");
  }
  newCStudent->next = NULL;

  if (head == NULL) {
    head = newCStudent;
  } else {
    cStudent *current = head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newCStudent;
  }

  front = front->next;
  free(temp);

  count--;
  printf("Admission confirmed for the front student\n");
}

void display() {
  if (front == NULL) {
    printf("Queue is empty\n");
    return;
  }

  Student *temp = front;
  while (temp != NULL) {
    printf("ID: %d, Name: %s, Priority: %d\n", temp->id, temp->name, temp->priority);
    temp = temp->next;
  }
}

void displayconfirmstudent() {
  if (head == NULL) {
    printf("Admission is not confirmed\n");
    return;
  }

  cStudent *temp = head;
  while (temp != NULL) {
    printf("ID: %d, Name: %s, Division: %s\n", temp->id, temp->name, temp->division);
    temp = temp->next;
  }
}

void addmarks(int id) {
  int ciemarks, esemarks, i = 0,g;
  if (head == NULL) {
    printf("No confirmed students yet\n");
    return;
  }

  cStudent *current = head;
  while (current != NULL) {
    if (current->id == id) {
      while (i < 3) {
          g=0;
        printf("Enter subject name: ");
        scanf("%s", current->subjects[i].subjectName);
        printf("Enter marks for %s (CIE): ", current->subjects[i].subjectName);
        scanf("%d", &current->subjects[i].cie);
        printf("Enter marks for %s (ESE): ", current->subjects[i].subjectName);
        scanf("%d", &current->subjects[i].ese);
        g=current->subjects[i].cie+current->subjects[i].ese;
        
        if(g>95){
         strcpy(current->subjects[i].subjectg,"O"); 
        }
        else if(g>90){
         strcpy(current->subjects[i].subjectg,"A+"); 
        }
        else if(g>80){
         strcpy(current->subjects[i].subjectg,"A"); 
        }
        else if(g>70){
         strcpy(current->subjects[i].subjectg,"B+"); 
        }
        
        else if(g>60){
         strcpy(current->subjects[i].subjectg,"B"); 
        }
        
        else if(g>50){
         strcpy(current->subjects[i].subjectg,"C+"); 
        }
        else if(g>40){
         strcpy(current->subjects[i].subjectg,"C"); 
        }
        else if(g>30){
         strcpy(current->subjects[i].subjectg,"D"); 
        }
        else {
         strcpy(current->subjects[i].subjectg,"F"); 
        }
        
        i++;
      }
      printf("CIE and ESE marks updated for student with ID %d\n", id);
      return;
    }

    current = current->next;
  }

  printf("Student with ID %d not found\n", id);
}

void displayresult(int id) {
  if (head == NULL) {
    printf("No students to display\n");
    return;
  }

  cStudent *temp = head;
  while (temp != NULL) {
    if (temp->id == id) {
      printf("\n");
      printf("+------------------------------------------+\n");
      printf("|              Student Result               |\n");
      printf("+------------------------------------------+\n");
      printf("| ID:       | %-15d |\n", temp->id);
      printf("| Name:     | %-15s |\n", temp->name);
      printf("| Division: | %-15s |\n", temp->division);
      printf("+------------------------------------------+\n");
      printf("| Subject   | CIE Marks | ESE Marks |Grade\n");
      printf("+------------------------------------------+\n");
      for (int i = 0; i < 3; i++) {
        printf("| %-10s | %-10d | %-10d | %s |\n", temp->subjects[i].subjectName, temp->subjects[i].cie, temp->subjects[i].ese,temp->subjects[i].subjectg);
      }
      printf("+------------------------------------------+\n");
      return;
    }

    temp = temp->next;
  }

  printf("Student with ID %d not found\n", id);
}

int main() {
  int choice, id, priority, per, i, p, pa,ch;
  char name[50];
  printf("Teacher and Student System\n");
  while(1) {
      
  printf("Enter your ID: ");
  scanf("%d", &i);
  printf("Enter your password: ");
  scanf("%d", &pa);

  if (pa==100) {
    do {
      printf("\n1. Enqueue\n2. Dequeue\n3. Display Queue\n4. Confirm Admission\n5. Delete Student\n6. Display Confirmed Students\n7. Add Marks\n8. Display Student Result\n9. Exit\nEnter your choice: ");
      scanf("%d", &choice);

      switch (choice) {
        case 1:
          if (count < 2) {
            printf("Enter student ID: ");
            scanf("%d", &id);
            printf("Enter student name: ");
            scanf("%s", name);
            printf("Enter student percentage: ");
            scanf("%d", &priority);
            enqueue(id, name, priority);
          } else {
            printf("Now Addmission ");
            printf("Enter student ID: ");
            scanf("%d", &id);
            printf("Enter student name: ");
            scanf("%s", name);
            printf("Enter student percentage: ");
            scanf("%d", &priority);
            priorityEnqueue(id, name, priority);
          }
          break;

        case 2:
          dequeue();
          break;

        case 3:
          display();
          break;

        case 4:
          confirmAdmission();
          break;

        case 5:
          printf("Enter ID to delete: ");
          scanf("%d", &id);
          deleteStudent(id);
          break;

        case 6:
          displayconfirmstudent();
          break;

        case 7:
          printf("Enter student ID: ");
          scanf("%d", &id);
          addmarks(id);
          break;

        case 8:
          printf("Enter student ID to display result: ");
          scanf("%d", &id);
          displayresult(id);
          break;

        case 9:
          break;

        default:
          printf("Invalid choice\n");
      }
    }while(choice<=8);
  }
  else if(i==pa){
      do{
      printf("1.Addmission List\n2Merit list\n3.Check Your Result\n4.EXit\nEnter Your Choice");
      scanf("%d",&ch);
      switch(ch){
          case 1:
          display();
          break;
          case 2:
          displayconfirmstudent();
          break;
          case 3:
          printf("Enter student ID to display result: ");
          scanf("%d", &id);
          displayresult(id);
          break;
          case 4:
          break;
      }}while(ch<=3);
      }
  else {
    printf("Password is wrong\n");
  }}

  return 0;
}

