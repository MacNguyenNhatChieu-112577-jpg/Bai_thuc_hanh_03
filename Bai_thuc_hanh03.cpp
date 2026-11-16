#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char hoten[30];
	int masv;
	float d1,d2,d3;
}Data;
typedef struct tagNode{
	Data infor;
	struct tagNode *link;
}Node;
typedef struct {
	Node *pHead;
	Node *pTail;
	int spt;
}LList;

void initList(LList *L){
	L->pHead = NULL;
	L->pTail = NULL;
	L->spt = 0;
}

int emptyList(LList L){
	return L.spt == 0;
}

void nhap(Data *x){
	printf("Nhap ma SV: ");
	scanf("%d", &x->masv);
	if(x->masv >0){
		getchar();
		printf("Nhap ho ten: ");
		fgets(x->hoten, sizeof(x->hoten),stdin);
		x->hoten[strcspn(x->hoten,"\n")] = '\0';
		
		printf("Nhap diem mon 1: ");
		scanf("%f",&x->d1);
		
		printf("Nhap diem mon 2: ");
		scanf("%f",&x->d2);
		
		printf("Nhap diem mon 3: ");
		scanf("%f",&x->d3);
	}
}

void in(Data x){
	printf("%-25s %-10 %.2f %.2f %.2f\n",x.hoten,x.masv,x.d1,x.d2,x.d3);
}
Node* taoNode(Data x){
	Node *p = (Node*)malloc(sizeof(Node));
	if(p == NULL){
		printf("Khong du bo nho!\n");
		exit(1);
	}
	p->infor = x;
	p->link = NULL;
	return p;
}

void insert_Head(LList *L,Data x){
	Node *p = taoNode(x);
	if(emptyList(*L)){
		L->pHead = p;
		L->pTail = p;
	}
	else{
		p->link = L->pHead;
		L->pHead = p;
	}
	L->spt++;
}
void insert_Tail(LList *L,Data x){
	Node *p = taoNode(x);
	if(emptyList(*L)){
		L->pHead = p;
		L->pTail = p;
	}
	else{
		L->pHead->link = p;
		L->pTail = p;
	}
	L->spt++;
}
Node* timMa(LList L, int ma){
	Node *p = L.pHead;
	while(p != NULL){
		if(p->infor.masv == ma)
			return p;
		p = p->link;
	}
	return NULL;
}

void insert_After(LList *L,int ma,Data x){
	Node *q = timMa(*L,ma);
	if(q == NULL){
		printf("Khong tim thay ma sinh vien!\n");
		return;
	}
	Node *p = taoNode(x);
	
	p->link = q->link;
	q->link = p;
	
	if(q == L->pTail)
		L->pTail = p;
		
	L->spt++;
}

void processList(LList L){
	Node *p = L.pHead;
	if(emptyList(L)){
		printf("Danh sach rong !\n");
		return;
	}
	printf("\n-25s %-10s %s\n","Ho ten" , "Ma SV", "Diem 1 Diem 2 Diem 3");
	while(p != NULL){
		in(p->infor);
		p = p->link;
	}
	printf("Tong so sinh vien: %d\n", L.spt);
}

void xoaMa(LList *L, int ma){
	Node *p = L->pHead;
	Node *q = NULL;
	while(p != NULL){
		if(p->infor.masv == ma){
			if(q == NULL)
				L->pHead = p->link;
			else
				q->link = p->link;
			if(p == L->pTail)
				L->pTail = q;
			free(p);
			L->spt--;
			
			printf("Da xoa sinh vien!\n");
			return;
		}
		q = p;
		p = p->link;
	}
	printf("Khong tim thay sinh vien!\n");
}
void xoaTen(LList *L,char ten[]){
	Node *p = L->pHead;
	Node *q = NULL;
	int dem = 0;
	while(p != NULL){
		if(strcmp(p->infor.hoten,ten) == 0){
			Node *temp = p;
			if(q == NULL) L->pHead = p->link;
			else q->link = p->link;
			if(p == L->pTail) L->pTail = q;
			p =p->link;
			free(temp);
			L->spt--;
			dem++;
		}
		else{
			q = p;
			p = p->link;
		}
	}
	printf("Da xoa %d sinh vien!\n", dem);
}
void timKiemMa(LList L,int ma){
	Node *p = timMa(L,ma);
		if(p == NULL){
			printf("Khogn tim thay!\n");
		}
		else in(p->infor);
	
}

void timKiemTen(LList L, char ten[]){
	Node *p = L.pHead;
	int dem = 0;
	while(p!= NULL){
		if(strcmp(p->infor.hoten,ten) == 0){
			in(p->infor);
			dem++;
		}
		p = p->link;
	}
	if(dem == 0){
		printf("Khong tim thay!\n");
	}
}

void sapXep(LList *L){
	Node *p,*q;
	Data temp;
	for(p = L->pHead;p != NULL; p->link){
		for(q = p->link;q != NULL; q = q->link){
			if(strcmp(p->infor.hoten,q->infor.hoten)>0){
				temp = p->infor;
				p->infor = q->infor;
				q->infor = temp;
			}
		}
	}
	printf("Da sap xep theo danh sach!\n");
}

void tachDanhSach(LList *L,LList *L2){
	initList(L2);
	Node *p = L->pHead;
	L->pHead = NULL;
	L->pTail = NULL;
	L->spt = 0;
	int dem = 1;
	while(p!= NULL){
		Node *temp = p;
		p = p->link;
		temp->link = NULL;
		
		LList *dich;
		if(dem %2 == 1) dich = L;
		else dich = L2;
		if(emptyList(*dich)){
			dich->pHead = temp;
			dich->pTail = temp;
		}
		else{
			dich->pTail->link = temp;
			dich->pTail = temp;
		}
		dich->spt++;
		dem++;
	}
}

void ghepDanhSach(LList *L,LList *L2){
	if(emptyList(*L2)){
		printf("Danh sach thu hai rong!\n");
		return;
	}
	if(emptyList(*L)){
		*L = *L2;
	}
	else{
		L->pTail->link = L2->pHead;
		L->pTail = L2->pTail;
		L->spt += L2->spt;
	}
	initList(L2);
	printf("Da ghep hai danh sach!\n");
}

void giaiPhong(LList *L){
	Node *p = L->pHead;
	while(p!= NULL){
		Node *temp = p;
		p = p->link;
		free(temp);
	}
	initList(L);
}
int main(){
	LList L, L2;
	Data x;
	int chon,ma;
	char ten[30];
	initList(&L);
	initList(&L2);
	do{
		printf("======== QUAN LY SINH VIEN ========\n");
		printf("1. Them vao dau danh sach\n");
		printf("2. Them vao cuoi danh sach\n");
		printf("3. Them vao mot sinh vien\n");
		printf("4. Xoa theo ma sinh vien\n");
		printf("5. Tim kiem theo ma\n");
		printf("6. Tim kiem theo ma\n");
		printf("7. Tim kiem theo ten\n");
		printf("8. Sap xep theo ten\n");
		printf("9. In danh sach\n");
		printf("10. Tach danh sach\n");
		printf("11. Ghep danh sach\n");
		printf("12. In danh sach thu hai\n");
		printf("0. Thoat\n");
		
		printf("Moi ban chon: ");
		scanf("%d", &chon);
		
		switch(chon){
			case 1:
				nhap(&x);
				if(x.masv > 0)
					insert_Head(&L,x);
				break;
			case 2:
				nhap(&x);
				if(x.masv > 0)
					insert_Tail(&L,x);
				break;
			case 3:
				printf("Nhap ma sinh vien can chen sau: ");
				scanf("%d", &ma);
				nhap(&x);
				if(x.masv > 0)
					insert_After(&L,ma,x);
				break;
			case 4:
				printf("Nhap ma can xoa: ");
				scanf("%d",&ma);
				xoaMa(&L,ma);
				break;
			case 5:
				getchar();
				printf("Nhap ten can xoa: ");
				fgets(ten,sizeof(ten),stdin);
				ten[strcspn(ten,"\n")] = '\0';
				timKiemTen(L,ten);
				break;
			case 6:
				printf("Nhap ma can tim: ");
				scanf("%d",&ma);
				timKiemMa(L,ma);
				break;
			case 7:
				getchar();
				printf("Nhap ho ten can tim: ");
				fgets(ten,sizeof(ten),stdin);
				ten[strcspn(ten,"\n")] = '\0';
				timKiemTen(L,ten);
				break;
			case 8:
				sapXep(&L);
				break;
			case 9:
				processList(L);
				break;
			case 10:
				tachDanhSach(&L,&L2);
				printf("Danh sach 1:\n");
				processList(L);
				printf("Danh sach 2:\n");
				processList(L2);
				break;
			case 11:
				ghepDanhSach(&L,&L2);
				break;
			case 12:
				processList(L2);
				break;
			case 0:
				giaiPhong(&L);
				giaiPhong(&L2);
				printf("Bye bye!\n");
				break;
			default:
				printf("Lua chon khong hop le!\n");
		}
	}while(chon != 0);
	return 0;
}
