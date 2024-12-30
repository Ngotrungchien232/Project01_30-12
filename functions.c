
#include <stdio.h>
#include "functions.h"
#include <string.h>
void menuStart(){
    printf("\n***He thong Quan ly Sinh vien C***\n");
    printf("\n");
    printf("\t  CHON VAI TRO CUA BAN\n");
    printf("\t=====================\n");
    printf("\t[1] Admin.\n");
    printf("\t[2] Student.\n");
    printf("\t[3] Teacher. \n");
    printf("\t[0] Thoat chuong trinh.\n");
    printf("\t=====================\n");
}
void menuAdmin(){
    printf("\n***He thong Quan ly Sinh vien Su dung C***\n");
    printf("\n");
    printf("\t          MENU\n");
    printf("\t==========================\n");
    printf("\t[1] Quan ly sinh vien.\n");
    printf("\t[2] Quan ly lop hoc.\n");
    printf("\t[3] Quan ly giao vien.\n");
    printf("\t[4] Huong dan nguoi dung.\n");
    printf("\t[0] Back.\n");
    printf("\t==========================\n");
}
void menuStudents(){
    printf("\n***He thong quan ly sinh vien su dung C***\n");
    printf("\n");
    printf("\t    STUDENT MENU\n");
    printf("\t======================\n");
    printf("\t[1] Them sinh vien moi.\n");
    printf("\t[2] Hien thi danh sach sinh vien.\n");
    printf("\t[3] Xoa mot sinh vien.\n");
    printf("\t[4] Chinh sua thong tin mot sinh vien.\n");
    printf("\t[5] Tim kiem mot sinh vien\n");
    printf("\t[6] Sap xep sinh vien.\n");
    printf("\t[0] Thoat.\n");
    printf("\t======================\n");
}
void addStudent(int *length, struct Student sv[]){
    printf("\n\t***Them mot sinh vien***\n");
	int newStudents;
    printf("\nThem so luong hoc sinh: ");
    scanf("%d", &newStudents);
    getchar(); 
    int i;
    for(i=*length;i<*length+newStudents;i++){
        printf("\n       Student %d\n", i + 1);
        printf("Nhap Id sinh vien: ");
        fgets(sv[i].studentId, 10, stdin);
        sv[i].studentId[strcspn(sv[i].studentId, "\n")]= '\0'; 
        printf("Nhap ten sinh vien: ");
        fgets(sv[i].fullName, 30, stdin);
        sv[i].fullName[strcspn(sv[i].fullName, "\n")]= '\0';
        printf("Nhap ngay sinh cho sinh vien (dd / mm / yyyy): \n");
        printf("   Nhap ngay sinh: ");
        scanf("%d", &sv[i].dateOfBrith.day);
        printf("   Nhap thang sinh: ");
        scanf("%d", &sv[i].dateOfBrith.month);
        printf("   Nhap nam sinh: ");
        scanf("%d", &sv[i].dateOfBrith.year);
        printf("Nhap gioi tinh cho sinh vien(1 for Male, 0 for Female): ");
        scanf("%d", &sv[i].gender);
        getchar(); 
        printf("Nhap lop cho sinh vien: ");
        fgets(sv[i].classroomId, 10, stdin);
        sv[i].classroomId[strcspn(sv[i].classroomId, "\n")] = '\0';
        printf("Nhap email cho sinh vien: ");
        fgets(sv[i].email, 30, stdin);
        sv[i].email[strcspn(sv[i].email, "\n")]= '\0';
        printf("Nhap so dien thoai cho sinh vien: ");
        fgets(sv[i].phone, 20, stdin);
        sv[i].phone[strcspn(sv[i].phone, "\n")]= '\0';
        printf("Nhap mat khau cho sinh vien: ");
        fgets(sv[i].password, 20, stdin);
        sv[i].password[strcspn(sv[i].password, "\n")]= '\0';
    }
    *length += newStudents;
    printf("\nThem sinh vien thanh cong.\n");
}
void printHeader(){
	printf("\n\t  ***All Student***\n");
    printf("|============|=============|============================|=======================|============|============================|=====================|=====================|\n");
    printf("| ID         | ID Class    | FullName                   | Date Of Brith         | Gender     | Email                      | Phone               | Password            |\n");
    printf("|============|=============|============================|=======================|============|============================|=====================|=====================|\n");
}
void printStudent(int length, struct Student sv[]){
    int i;
    for(i=0;i<length;i++){
    printf("| %-11s| %-12s| %-27s| %02d/%02d/%04d            | %-11s| %-27s| %-20s| %-20s|\n",
            sv[i].studentId,
            sv[i].classroomId,
            sv[i].fullName,
            sv[i].dateOfBrith.day,
            sv[i].dateOfBrith.month,
            sv[i].dateOfBrith.year,
            sv[i].gender ? "Male" : "Female",
            sv[i].email,
            sv[i].phone,
            sv[i].password);
            printf("|------------|-------------|----------------------------|-----------------------|------------|----------------------------|---------------------|---------------------|\n");
    }
}
void saveStudentToFile(int length, struct Student sv[]){
    FILE *fptr = fopen("studentsData.dat", "wb");
    if (fptr == NULL) {
        printf("Khong the mo tep\n");
        return;
    }
    fwrite(sv, sizeof(struct Student), 50, fptr);
    printf("Du lieu sinh vien duoc luu thanh cong\n");
    fclose(fptr);
}
void loadStudentFromFile(int *length, struct Student sv[]){
    FILE *fptr = fopen("studentsData.dat", "rb");
    if (fptr == NULL) {
        printf("Khong tim thay du lieu.\n");
        return;
    }
    *length = fread(sv, sizeof(struct Student), 50, fptr);
    fclose(fptr);
}
void deleteStudent(int *length, struct Student sv[]) {
    printf("\n\t***Xoa mot sinh vien***\n");
    getchar();
	char id[10];
    printf("\nNhap ma sinh vien de xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int findIndex= -1;
    int i;
    for(i=0;i<*length; i++) {
        if(strcmp(sv[i].studentId, id) == 0) {
            findIndex= i;
            break;
        }
    }
    if(findIndex==-1) {
        printf("\nKhong tim thay sinh vien voi Id %s.\n", id);
    }else {
        printf("\nMot sinh vien da duoc tim thay voi Id: %s\n", id);
        printf("  Thong tin sinh vien:\n");
        printf("----------------------\n");
        printf("ID Class: %s\n",sv[findIndex].classroomId);
        printf("FullName: %s\n",sv[findIndex].fullName);
        printf("Date Of Brith: %02d/%02d/%04d\n",sv[findIndex].dateOfBrith.day,sv[findIndex].dateOfBrith.month,sv[findIndex].dateOfBrith.year);
        printf("Gender: %s\n",sv[findIndex].gender ? "Male" : "Female");
        printf("Email: %s\n",sv[findIndex].email);
        printf("Phone: %s\n",sv[findIndex].phone);
        printf("Password: %s\n",sv[findIndex].password);
        for(i=findIndex;i<*length-1; i++){
            sv[i]=sv[i+1];
        }
        (*length)--;
        printf("\n\t***Cap nhat thong tin sinh vien moi ***\n");
        printHeader();
        printStudent(*length, sv);
        printf("\nDa xoa sinh vien thanh cong.\n");
    }
}
void editStudent(int length, struct Student sv[]) {
    printf("\n\t***Chinh sua thong tin sinh vien***\n");
    getchar();
    char id[10];
    printf("\nNhap Id sinh vien can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int findIndex=-1;
    int i;
    for(i=0;i<length;i++) {
        if(strcmp(sv[i].studentId, id)==0) {
            findIndex=i;
            break;
        }
    }
    if (findIndex== -1) {
        printf("\nKhong tim thay sinh vien voi Id %s.\n", id);
    }else{
        printf("\nCo mot sinh vien voi Id: %s\n", id);
        printf("  Thong tin sinh vien:\n");
        printf("----------------------\n");
        printf("ID Class: %s\n",sv[findIndex].classroomId);
        printf("FullName: %s\n",sv[findIndex].fullName);
        printf("Date Of Brith: %02d/%02d/%04d\n",sv[findIndex].dateOfBrith.day,sv[findIndex].dateOfBrith.month,sv[findIndex].dateOfBrith.year);
        printf("Gender: %s\n",sv[findIndex].gender ? "Male" : "Female");
        printf("Email: %s\n",sv[findIndex].email);
        printf("Phone: %s\n",sv[findIndex].phone);
        printf("Password: %s\n",sv[findIndex].password);
        printf("\nNhap ten moi: ");
        fgets(sv[findIndex].fullName, 30, stdin);
        sv[findIndex].fullName[strcspn(sv[findIndex].fullName, "\n")]= '\0';
        printf("Nhap vao ngay , thang, nam sinh moi (dd / mm / yyyy):\n");
        printf("   Nhap vao ngay sinh: ");
        scanf("%d", &sv[findIndex].dateOfBrith.day);
        printf("   Nhap vao thang sinh: ");
        scanf("%d", &sv[findIndex].dateOfBrith.month);
        printf("   Nhap vao nam sinh: ");
        scanf("%d", &sv[findIndex].dateOfBrith.year);
        printf("Nhap gioi tinh (1 for Male, 0 for Female): ");
        scanf("%d", &sv[findIndex].gender);
        getchar();
        printf("Nhap lop hoc moi: ");
        fgets(sv[findIndex].classroomId, 10, stdin);
        sv[findIndex].classroomId[strcspn(sv[findIndex].classroomId, "\n")]= '\0';
        printf("Nhap email moi: ");
        fgets(sv[findIndex].email, 30, stdin);
        sv[findIndex].email[strcspn(sv[findIndex].email, "\n")]= '\0';
        printf("Nhap so dien thoai moi: ");
        fgets(sv[findIndex].phone, 20, stdin);
        sv[findIndex].phone[strcspn(sv[findIndex].phone, "\n")]= '\0';
        printf("Nhap mat khau moi: ");
        fgets(sv[findIndex].password, 20, stdin);
        sv[findIndex].password[strcspn(sv[findIndex].password, "\n")]= '\0';
        printf("\n\t***Cap nhat sinh vien moi***\n");
        printHeader();
        printStudent(length, sv);
        printf("\nSinh vien da chinh sua thanh cong.\n");
    }
}
void searchStudent(int length, struct Student sv[]){
    printf("\n\t***Tim kiem mot sinh vien***\n");
    getchar();
	char name[30];
    printf("\Nhap ten de tim kiem sinh vienn: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    int i;
    int findIndex=-1;
	for(i=0;i<length; i++) {
        if (strcmp(sv[i].fullName,name)==0){
            findIndex=i;
            break;
        }
    }
    if (findIndex==-1){
        printf("\nKhong tim thay sinh vien nao voi ten %s.\n",name);
    }else{
        printf("\nSinh vien duoc tim thay voi ten %s.\n",name);
        printf("Da tim thay sinh vien thanh cong.\n\n");
	}
}
void sortStudentsByName(int length, struct Student sv[]){
    int choice4;
	do{
		printf("\n\t***Sap xep mot sinh vien***\n");
	    printf("\n");
	    printf("\t  Sap xep sinh vien\n");
	    printf("\t=====================\n");
	    printf("\t[1] Sap xep tang dan.\n");
	    printf("\t[2] Sap xep giam dan.\n");
	    printf("\t[0] Thoat.\n");
	    printf("\t=====================\n");
		printf("\tNhap vao lua chon cua ban: ");
	    scanf("%d", &choice4);
		switch(choice4){
			struct Student temp;
			int i,j;
			case 1:
			    printf("\n\t  Sap xep tang dan\n");
				for(i=0;i<length;i++) {
			        for(j=i+1;j<length-i-1;j++) {
			            if(strcmp(sv[i].fullName, sv[j].fullName)>0){
			                temp = sv[i];
			                sv[i] = sv[j];
			                sv[j] = temp;
			            }
			        }
			    }
			    printHeader();
		        printStudent(length,sv);
			    printf("\nHoc sinh duoc sap xep thanh cong.\n");
				break;
			case 2:
				printf("\n\t  Sap xep giam dan\n");
				for(i=0;i<length;i++) {
			        for(j=i+1;j<length-i-1;j++) {
			            if(strcmp(sv[i].fullName, sv[j].fullName)<0){
			                temp=sv[i];
			                sv[i]=sv[j];
			                sv[j]=temp;
			            }
			        }
			    }
			    printHeader();
		        printStudent(length,sv);
			    printf("\nHoc sinh duoc sap xep thanh cong.\n");
				break;
			case 0:
				break;
			default:
				printf("\tLoi: moi ban nhap lai.\n");
	    }
	}while(choice4!=0);
}
void menuTeacher(){
    printf("\n***Quan ly giao vien bang ngon ngu C***\n");
    printf("\n");
    printf("\t    TEACHER MENU\n");
    printf("\t======================\n");
    printf("\t[1] Them mot giao vien moi.\n");
    printf("\t[2] Hien thi danh sach giao vien.\n");
    printf("\t[3] Xoa mot giao vien.\n");
    printf("\t[4] Chinh sua thong tin mot giao vien.\n");
    printf("\t[5] Tim kiem mot giao vien.\n");
    printf("\t[6] Sap xep giao vien.\n");
    printf("\t[7] Them giao vien vao lop hoc.\n");
    printf("\t[0] Thoat.\n");
    printf("\t======================\n");
}	
void addTeacher(int *length, struct Teacher tv[]){
    printf("\n\t***Them mot giao vien moi***\n");
	int newTeacher;
    printf("\nThem so luong giao vien: ");
    scanf("%d", &newTeacher);
    getchar(); 
    int i;
    for(i=*length;i<*length+newTeacher;i++){
        printf("\n       Giao vien %d\n", i + 1);
        printf("Nhap ID: ");
        fgets(tv[i].teacherId, 10, stdin);
        tv[i].teacherId[strcspn(tv[i].teacherId, "\n")]= '\0'; 
        printf("Nhap ten: ");
        fgets(tv[i].fullName, 30, stdin);
        tv[i].fullName[strcspn(tv[i].fullName, "\n")]= '\0';
        printf("Nhap ngay, thang, nam sinh (dd / mm / yyyy): \n");
        printf("   Nhap ngay sinh: ");
        scanf("%d", &tv[i].dateOfBrith.day);
        printf("   Nhap thang sinh: ");
        scanf("%d", &tv[i].dateOfBrith.month);
        printf("   Nhap nam sinh: ");
        scanf("%d", &tv[i].dateOfBrith.year);
        printf("Nhap gioi tinh(1 for Male, 0 for Female): ");
        scanf("%d", &tv[i].gender);
        getchar(); 
        printf("Nhap lop: ");
        fgets(tv[i].classroomId, 10, stdin);
        tv[i].classroomId[strcspn(tv[i].classroomId, "\n")] = '\0';
        printf("Nhap email: ");
        fgets(tv[i].email, 30, stdin);
        tv[i].email[strcspn(tv[i].email, "\n")]= '\0';
        printf("Nhap so dien thoai: ");
        fgets(tv[i].phone, 20, stdin);
        tv[i].phone[strcspn(tv[i].phone, "\n")]= '\0';
        printf("Nhap mat khau: ");
        fgets(tv[i].password, 20, stdin);
        tv[i].password[strcspn(tv[i].password, "\n")]= '\0';
    }
    *length += newTeacher;
    printf("\nThem giao vien thanh cong.\n");
}
void printHeader2(){
	printf("\n\t  ***All Teacher***\n");
    printf("|============|=============|============================|=======================|============|============================|=====================|=====================|\n");
    printf("| ID         | ID Class    | FullName                   | Date Of Brith         | Gender     | Email                      | Phone               | Password            |\n");
    printf("|============|=============|============================|=======================|============|============================|=====================|=====================|\n");
}		
void printTeacher(int length, struct Teacher tv[]){
    int i;
    for(i=0;i<length;i++){
    printf("| %-11s| %-12s| %-27s| %02d/%02d/%04d            | %-11s| %-27s| %-20s| %-20s|\n",
            tv[i].teacherId,
            tv[i].classroomId,
            tv[i].fullName,
            tv[i].dateOfBrith.day,
            tv[i].dateOfBrith.month,
            tv[i].dateOfBrith.year,
            tv[i].gender ? "Male" : "Female",
            tv[i].email,
            tv[i].phone,
            tv[i].password);
            printf("|------------|-------------|----------------------------|-----------------------|------------|----------------------------|---------------------|---------------------|\n");
    }
}
void saveTeacherToFile(int length, struct Teacher tv[]){
    FILE *fptr = fopen("teachersData.dat", "wb");
    if (fptr == NULL) {
        printf("Khong the mo file \n");
        return;
    }
    fwrite(tv, sizeof(struct Teacher), 50, fptr);
    printf("Du lieu giao vien duoc luu thanh cong\n");
    fclose(fptr);
}
void loadTeacherFromFile(int *length, struct Teacher tv[]){
    FILE *fptr = fopen("teachersData.dat", "rb");
    if (fptr == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    *length = fread(tv, sizeof(struct Teacher), 50, fptr);
    fclose(fptr);
}
void deleteTeacher(int *length, struct Teacher tv[]) {
    printf("\n\t***Xoa mot giao vien***\n");
    getchar();
	char id[10];
    printf("\nNhap Id giao vien de xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int findIndex= -1;
    int i;
    for(i=0;i<*length; i++) {
        if(strcmp(tv[i].teacherId, id) == 0) {
            findIndex= i;
            break;
        }
    }
    if(findIndex==-1) {
        printf("\nKhong co giao vien nao duco tim thay voi Id.\n", id);
    }else {
        printf("\nCo mot giao vien voi Id: %s\n", id);
        printf("  Thong tin giao vien:\n");
        printf("----------------------\n");
        printf("ID Class: %s\n",tv[findIndex].classroomId);
        printf("FullName: %s\n",tv[findIndex].fullName);
        printf("Date Of Brith: %02d/%02d/%04d\n",tv[findIndex].dateOfBrith.day,tv[findIndex].dateOfBrith.month,tv[findIndex].dateOfBrith.year);
        printf("Gender: %s\n",tv[findIndex].gender ? "Male" : "Female");
        printf("Email: %s\n",tv[findIndex].email);
        printf("Phone: %s\n",tv[findIndex].phone);
        printf("Password: %s\n",tv[findIndex].password);
        for(i=findIndex;i<*length-1; i++){
            tv[i]=tv[i+1];
        }
        (*length)--;
        printf("\n\t***Cap nhat giao vien moi ***\n");
        printHeader2();
        printTeacher(*length, tv);
        printf("\nGiao vien da xoa thanh cong.\n");
    }
}
void editTeacher(int length, struct Teacher tv[]) {
    printf("\n\t***Chinh sua thong tin mot giao vien***\n");
    getchar();
    char id[10];
    printf("\nNhap Id giao vien de chinh sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int findIndex=-1;
    int i;
    for(i=0;i<length;i++) {
        if(strcmp(tv[i].teacherId, id)==0) {
            findIndex=i;
            break;
        }
    }
    if (findIndex== -1) {
        printf("\nKhong co giao vien nao voi Id %s.\n", id);
    }else{
        printf("\nMot giao vien duoc tim thay voi Id: %s\n", id);
        printf("  Thong tin giao vien:\n");
        printf("----------------------\n");
        printf("ID Class: %s\n",tv[findIndex].classroomId);
        printf("FullName: %s\n",tv[findIndex].fullName);
        printf("Date Of Brith: %02d/%02d/%04d\n",tv[findIndex].dateOfBrith.day,tv[findIndex].dateOfBrith.month,tv[findIndex].dateOfBrith.year);
        printf("Gender: %s\n",tv[findIndex].gender ? "Male" : "Female");
        printf("Email: %s\n",tv[findIndex].email);
        printf("Phone: %s\n",tv[findIndex].phone);
        printf("Password: %s\n",tv[findIndex].password);
        printf("\nENhap ten moi: ");
        fgets(tv[findIndex].fullName, 30, stdin);
        tv[findIndex].fullName[strcspn(tv[findIndex].fullName, "\n")]= '\0';
        printf("Nhap vao ngay, thang, nam sinh (dd / mm / yyyy):\n");
        printf("   Nhap ngay sinh: ");
        scanf("%d", &tv[findIndex].dateOfBrith.day);
        printf("   Nhap thang sinh: ");
        scanf("%d", &tv[findIndex].dateOfBrith.month);
        printf("   Nhap nam sinh: ");
        scanf("%d", &tv[findIndex].dateOfBrith.year);
        printf("Nhap gioi tinh (1 for Male, 0 for Female): ");
        scanf("%d", &tv[findIndex].gender);
        getchar();
        printf("Nhap vao lop moi: ");
        fgets(tv[findIndex].classroomId, 10, stdin);
        tv[findIndex].classroomId[strcspn(tv[findIndex].classroomId, "\n")]= '\0';
        printf("Nhap vao email moi: ");
        fgets(tv[findIndex].email, 30, stdin);
        tv[findIndex].email[strcspn(tv[findIndex].email, "\n")]= '\0';
        printf("Nhap so dien thoai: ");
        fgets(tv[findIndex].phone, 20, stdin);
        tv[findIndex].phone[strcspn(tv[findIndex].phone, "\n")]= '\0';
        printf("Nhap mat khau: ");
        fgets(tv[findIndex].password, 20, stdin);
        tv[findIndex].password[strcspn(tv[findIndex].password, "\n")]= '\0';
        printf("\n\t***Cap nhat giao vien moi***\n");
        printHeader2();
        printTeacher(length, tv);
        printf("\nGiao vien da chinh sua thanh cong.\n");
    }
}
void searchTeacher(int length, struct Teacher tv[]){
    printf("\n\t***Tim kiem mot giao vien***\n");
    getchar();
	char name[30];
    printf("\nNhap ten giao vien de tim kiem: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    int i;
    int findIndex=-1;
	for(i=0;i<length; i++) {
        if (strcmp(tv[i].fullName,name)==0){
            findIndex=i;
            break;
        }
    }
    if (findIndex==-1){
        printf("\nKhong tim thay giao vien nao voi ten %s.\n",name);
    }else{
        printf("\nGiao vien da duoc tim thay voi ten %s.\n",name);
        printf("Giao vien da duoc tim thay thanh cong.\n\n");
	}
}
void sortTeachersByName(int length, struct Teacher tv[]){
    int choice6;
	do{
		printf("\n\t***Sap xep mot giao vien***\n");
	    printf("\n");
	    printf("\t  Sap xep giao vien\n");
	    printf("\t=====================\n");
	    printf("\t[1] Tang dan.\n");
	    printf("\t[2] Giam dan.\n");
	    printf("\t[0] Thoat.\n");
	    printf("\t=====================\n");
		printf("\tNhap vao lua chon cua ban: ");
	    scanf("%d", &choice6);
		switch(choice6){
			struct Teacher temp;
			int i,j;
			case 1:
			    printf("\n\t  Sap xep theo cach tang dan\n");
				for(i=0;i<length;i++) {
			        for(j=i+1;j<length-i-1;j++) {
			            if(strcmp(tv[i].fullName, tv[j].fullName)>0){
			                temp = tv[i];
			                tv[i] = tv[j];
			                tv[j] = temp;
			            }
			        }
			    }
			    printHeader2();
		        printTeacher(length,tv);
			    printf("\nGiao vien duoc bo tri thanh cong.\n");
				break;
			case 2:
				printf("\n\t  Sap xep theo cach giam dan\n");
				for(i=0;i<length;i++) {
			        for(j=i+1;j<length-i-1;j++) {
			            if(strcmp(tv[i].fullName, tv[j].fullName)<0){
			                temp=tv[i];
			                tv[i]=tv[j];
			                tv[j]=temp;
			            }
			        }
			    }
			    printHeader2();
		        printTeacher(length,tv);
			    printf("\nGiao vien duoc bo tri thanh cong.\n");
				break;
			case 0:
				break;
			default:
				printf("\tLoi: Vui long thu lai.\n");
	    }
	}while(choice6!=0);
}



