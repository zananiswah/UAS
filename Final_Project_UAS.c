/* Proyek Akhir Pemrogram Lanjut Semester 2
Kelas           : Pemrograman Lanjut -02
Kelompok        : 8
Nama Anggota    :
        - Amanda Fairuz Syifa     (2006535653)
        - Firzy Allen             (2006577555)
        - Steven Yosua Saputra    (2006577290)
        - Zana Niswah Awahita     (2006577593)
Judul Proyek    : Program Perampungan dan Pembuatan SKL
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <omp.h>

#define MAX_LENGTH 256
#define SIZE 100

//Inisialisasi function prototype
int search_database_sekolah(char input[]);
int display_database_sekolah();
int display_database_nilai(char nama_pelajaran[][SIZE]);
int display_menu();
int display_panduan();
int input_data(char nama_pelajaran[][SIZE]);
int olah_data(int array[]);

//Inisialisasi struct untuk input data siswa
struct siswa{
    char nama[SIZE];
    int sekolah;
    int nilai[SIZE];
    char TTL[SIZE];
    int NIS;
    int NISN;
    char kelas[SIZE];
    struct siswa *next;
};

int lihat_data_siswa(struct siswa *data,char nama_pelajaran[][SIZE]);
int cetak_SKL(struct siswa *data1);

struct siswa *head = NULL;
struct siswa *ptr = NULL;
struct siswa *temp = NULL;

int main(){
	int sentinel_1 = 0;
	
    struct siswa *data = NULL;
    struct siswa *data1 = NULL;
    
    //Penjelasan program secara singkat
    printf ("\n\n\t===============================================================================================");
	printf ("\n\t\t\t\t\tPROGRAM PERAMPUNGAN DAN PEMBUATAN SKL");
	printf ("\n\t===============================================================================================");
	printf ("\n\n         Program ini dapat membantu pendataan siswa dan proses pencetakan surat keterangan lulus (SKL).");
	printf ("\n\t\t\tSilahkan baca panduan untuk mengetahui cara menggunakan program!\n");
	printf ("\n\n\t\t\t\tSilahkan tekan tombol apapun untuk melanjutkan...");
	getch ();
	system("cls");
	
    menu:
    //Program menampilkan menu yang tersedia
	display_menu();
	int pilihan;
	char input[SIZE];
    char nama_pelajaran[SIZE][SIZE];
    display_database_nilai(nama_pelajaran);
    
    //User memasukkan menu yang diinginkan
    printf("\n\t\tMasukkan Pilihan: ");
    scanf("%d", &pilihan);
            
    switch(pilihan){
        case 1 :
            //Input data siswa 
            system("cls");
            input_data(nama_pelajaran);
            system("cls");
            sentinel_1 = 1;
            goto menu;
            break;
                    
        case 2 :
            //Lihat data siswa
            if(sentinel_1 == 1){
		        system("cls");
		        lihat_data_siswa(data,nama_pelajaran);
		        printf("\n\t\tSilahkan tekan tombol apapun untuk melanjutkan...");
		        getch();
		        system("cls");
		        goto menu;	
			}
			
			else{
				system ("cls");
				printf ("\n\n\t\tMasukkan input data siswa terlebih dahulu.");
				printf ("\n\n\t\tSilahkan tekan tombol apapun untuk melanjutkan...");
				getch ();
				system ("cls");
				goto menu;
			}
            break;
                    
        case 3 :
        	//Lihat daftar sekolah
            system("cls");
            int temp_display;
            temp_display=display_database_sekolah();
            if (temp_display==1){
                system("cls");
                printf("\t\t===========================================\n");
			    printf("\t\t\t    MENCARI NAMA SEKOLAH\n");
			    printf("\t\t===========================================\n\n");
			    printf("\t\tContoh: SMA Negeri 109 Jakarta\n\n");
                printf("\t\tMasukkan nama sekolah Anda: ");
                scanf(" %[^\n]", input);
                search_database_sekolah (input);
                printf("\n\t\tSilahkan tekan tombol apapun untuk melanjutkan...");
                getch();
                system("cls");
                goto menu;
            }
            if (temp_display==0){
                system("cls");
                goto menu;
            }
            break;
                    
        case 4 :    
            //cetak SKL
            
             if(sentinel_1 == 1){
		        system("cls");
		        cetak_SKL(data1);
		        printf("\n\n\n\t\tSilahkan tekan tombol apapun untuk melanjutkan...\n");
		        getch();
		        system("cls");
		        goto menu;	
			}
			
			else{
				system ("cls");
				printf ("\n\n\t\tMasukkan input data siswa terlebih dahulu.");
				printf ("\n\n\t\tSilahkan tekan tombol apapun untuk melanjutkan...");
				getch();
				system("cls");
				goto menu;
			}
            break;
                        
        case 5 :
            //Display panduan
            system("cls");
            display_panduan();
            system ("cls");
            goto menu;
            break;
        
		case 6 :
            //Keluar program
            system("cls");
            keluar();
            system ("cls");
            goto menu;
            break;
        	
		//Terdapat default untuk Error Handling apabila User memasukkan pilihan yang salah
        default :
            system ("cls");
            printf("Pilihan anda tidak sesuai.\nSilahkan ulangi pilihan\n");
            sleep (1);
            system("cls");
            goto menu;
    }
}

int display_menu (){
	printf("\t\t========================================\n");
    printf("\t\t\t       MENU LAYANAN\n");
    printf("\t\t========================================\n\n");
	printf ("\t\t\t1. Input Data Siswa\n");
	printf ("\t\t\t2. Lihat Data Siswa\n");
	printf ("\t\t\t3. Melihat Sekolah\n");
	printf ("\t\t\t4. Cetak SKL\n");
	printf ("\t\t\t5. Panduan\n");
	printf ("\t\t\t6. Keluar\n");
}

int display_database_nilai(char nama_pelajaran[][SIZE]){
	//Program membuka file database dari .txt
    char *file_database = "database_nilai.txt";
    FILE *fd = fopen(file_database,"r");
    int i=0, j=0;

    if(fd==NULL){
        printf("Error, cannot open the file");
        return 0;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, fd)){
    	for (i=0;i<strlen(buffer);i++){
            if (buffer[i]==';'){
            	break;
            }
            nama_pelajaran[j][i]=buffer[i];
        }
        j++;
    }
    fclose(fd);
}

int input_data(char nama_pelajaran[][SIZE]){
    int sentinel = 1;
    int i;
    char answer;
    
	system("cls");
	printf("\t\t==========================================================\n");
	printf("\t\t\t\t\tInput Data           \n");
	printf("\t\t==========================================================\n");

    while(sentinel != -1){
        temp = malloc(sizeof(struct siswa));
        ptr=head;
        printf("\n\t\tCatatan:\n\t\tNomor indeks sekolah dapat dilihat pada menu nomor 3.\n");
        //User menginput data sesuai kebutuhan program
        printf("\n\t\tNama\t\t\t: ");
        scanf(" %[^\n]", temp->nama);
        input_indeks:
        printf ("\n\t\tIndeks Sekolah\t\t: ");
        scanf (" %d",&temp->sekolah);
        printf("\n\t\tTempat, tanggal lahir\t: ");
        scanf(" %[^\n]", temp->TTL);
        printf("\n\t\tNIS\t\t\t: ");
        scanf(" %d", &temp->NIS);
        printf("\n\t\tNISN\t\t\t: ");
    	scanf(" %d", &temp->NISN);
        printf("\n\t\tKelas\t\t\t: ");
        scanf(" %[^\n]", temp->kelas);
        for (i=0;i<14;i++){
            printf("\n\t\tNilai %s\t: ", nama_pelajaran[i]);
            scanf(" %d", &temp->nilai[i]);
            if( temp->nilai[i] < 0 || temp->nilai[i] > 100){
                while(temp->nilai[i] < 0 || temp->nilai[i] > 100){
                    printf("\n\t\tMasukkan kembali nilai %s\t: ", nama_pelajaran[i]);
                    scanf(" %d", &temp->nilai[i]);
                }
            } 
            else{
                continue;
            }
        }
	    temp->next=NULL;
	    
	    printf("\n\t\t_____________________________________________________________");
	    answer:
	    printf("\n\n\t\tApakah Anda ingin memasukkan data kembali? (Y/N)");
	    printf("\n\t\tKetik Pilihan (Y=Ya)(N=Tidak): ");
	    scanf("%s", &answer);
	            
	    if(answer=='y'||answer=='Y'){
	        if(head==NULL){
	            head = temp;
	            continue;
	        }
	        while(ptr->next!=NULL){
	            ptr=ptr->next;
	        }
		    ptr->next=temp;
		    continue;
	    }
	                
	    else if(answer=='n'||answer=='N'){
	        if(head==NULL){
	            head = temp;
	            break;
	        }
	        while(ptr->next!=NULL){
	            ptr=ptr->next;
	        }
	        ptr->next=temp;
	        sentinel=-1;
	        continue;
	    }
	    else{
	        printf("\n\t\tInputan yang Anda masukkan salah.\n\t\tSilahkan memasukkan kembali input Anda.");
	        printf("\n\t\t_____________________________________________________________");
	        goto answer;
	    }
    }
}

int lihat_data_siswa(struct siswa *data, char nama_pelajaran[][SIZE]){
    int i;
    int counter=7;
    int j=1;
    int sentinel = 1;
    data = head;
    char buffer[MAX_LENGTH];
    
    printf ("\t\t========================================\n");
    printf ("\t\t\t\tDATA SISWA\n");
    printf ("\t\t========================================\n\n");
    
    while(sentinel==1){
    	//Menampilkan hasil input sesuai dengan input user
	    printf("\n\t\t1. Nama \t\t: %s", data->nama);
        printf ("\n\t\t2. Nama Sekolah \t: ");
        char *file_database = "database_sekolah.txt";
    	FILE *fd = fopen(file_database,"r");
    	
	    while (fgets(buffer, MAX_LENGTH, fd)){
	       if (j==data->sekolah){
				for (i=0;i<strlen(buffer);i++){
		            if (buffer[i]==';'){
		                printf(" ");
		                continue;
		            }
		            printf("%c", buffer[i]);
		        }
		        fclose(fd);
		    }
		    j++;
		}
        printf("\t\t3. TTL \t\t\t: %s", data->TTL);
        printf("\n\t\t4. NIS \t\t\t: %d", data->NIS);
        printf("\n\t\t5. NISN \t\t: %d", data->NISN);
        printf("\n\t\t6. Kelas \t\t: %s", data->kelas);
        
        for(i=0;i<14;i++){
            printf("\n\t\t%d. Nilai Siswa %s: %d",counter++,nama_pelajaran[i],data->nilai[i]);  
        }  
        
        data=data->next;
        j=1;
        counter = 7;
        printf("\n\t\t_____________________________________________________________\n");
        
        if(data == NULL){
            sentinel = -1;
    	}
    }
}

int display_database_sekolah(){
    int i;
    int counter=1;
    char temp;
    char *file_database = "database_sekolah.txt";
    FILE *fd = fopen(file_database,"r");

    if (fd==NULL){
        printf("\n\t\tError, cannot open the file");
        return 0;
    }

    char buffer[MAX_LENGTH];
    
    printf("\t\t===========================================\n");
    printf("\t\t\t\tLIST SEKOLAH\n");
    printf("\t\t===========================================\n\n");
    //Menampilkan list sekolah beserta NPSN yang telah terdaftar di database
    while (fgets(buffer, MAX_LENGTH, fd)){
        printf("\t\t %d. ", counter);
        for (i=0;i<strlen(buffer);i++){
            if (buffer[i]==';'){
                printf(" ");
                continue;
            }
            printf("%c", buffer[i]);
        }
        counter++;
    }
    fclose(fd);
    
    again:
    printf("\n\n\t\tApakah Anda ingin mencari nama sekolah Anda (Y/N)\n\t\tKetik Pilihan (Y=Ya)(N=Tidak): ");
    //getch();
    scanf("%s", &temp);
    if (temp=='Y'||temp=='y'){
        system("cls");
        return 1;
    }
    else if(temp=='N'||temp=='n'){
        system("cls");
        return 0;
    }
    else{
        printf("\n\t\t Pilihan Anda tidak sesuai.\n\t\t Silahkan memasukkan kembali pilihan Anda\n\n");
        goto again;
    }
}

int search_database_sekolah(char input[]){
    int temp=0;
    int counter = 1;
    char buffer_2[20];
    char nama[SIZE];
    int npsn_temp;
    
    char *file_database = "database_sekolah.txt";
    FILE *fd = fopen(file_database,"a++");

    if (fd==NULL){
        printf("Error, cannot open the file");
        return 0;
    }
	
    char buffer[MAX_LENGTH];
    int i;

    for (i=0;i<strlen(input);i++){
        input[i] = toupper(input[i]);
    }
    
    while (fgets(buffer, MAX_LENGTH, fd)){
        if (strncmp(buffer,input,strlen(input))==0){
            printf("\n\t\t%d. %s", counter, buffer);
            temp=1;
        }
        counter++;
    }
    
    //Memasukkan sekolah ke database
    if (temp==0){
        printf("\n\t\tNama sekolah Anda tidak terdaftar!");
        printf("\n\t\tMasukkan nama sekolah Anda (Memasukkan ke dalam database): ");
        getch();
        scanf("%[^\n]", &nama);
        printf("\n\t\tMasukkan NPSN sekolah Anda (Memasukkan ke dalam database): ");
        scanf("%d", &npsn_temp);
        for (i=0;i<strlen(nama);i++){
            nama[i] = toupper(nama[i]);
        }
        fprintf(fd,"\n%s;%d",nama,npsn_temp);
    }
    fclose(fd);
}

int olah_data (int array[]){
	omp_set_num_threads(4);
	float average, sum;
	
	//program akan menghitung jumlah total nilai siswa secara parallel
	#pragma omp parallel
	{
		int i;
		int localsum = 0;
		
		#pragma omp for
		for (i=0;i<14;i++){
			localsum += array[i];
		}
		#pragma omp critical
		sum += localsum;
	}
	average = sum/14;
	//Mencetak nilai rata-rata siswa
	printf("\n\t\t\xb3\t\t   RATA-RATA\t\t\t\t\t       \xb3\t %2.f\t     \xb3", average);

}

int cetak_SKL(struct siswa *data1){
    system ("cls");
    int counter = 1, print, i, j=1, k, counter2=0,l;
    char buffer[MAX_LENGTH];
	char temp[SIZE];
	data1 = head;
	
	printf("\t\t================================================\n");
    printf("\t\t\t\t     CETAK SKL\n");
    printf("\t\t================================================\n");
	printf("\t\t Nama-Nama Siswa:");
	while(data1 != NULL){
		printf("\n\n\t\t\t%d. %s", counter++, data1->nama);
		data1 = data1->next;
	}
	
	ulangi:
	printf("\n\n\t\tMasukkan nomor index yang ingin anda cetak: ");
	scanf("%d", &print);
	system ("cls");
	if(print >= counter)
		goto ulangi;
    
    data1 = head;
    
    for(i=1; i<= counter; i++){
    	if(i == print){
			printf("\n\t\t\t\t\t\t    DINAS PENDIDIKAN");
			printf("\n\t\t\t\t\t           ");
			
			char *file_database = "database_sekolah.txt";
	    	FILE *fd = fopen(file_database,"r");
		    while (fgets(buffer, MAX_LENGTH, fd)){
		       if (j==data1->sekolah){
					for (l=0;l<strlen(buffer);l++){
					    if (buffer[l]==';'){
					    	fclose(fd);
			                break;
			            }
			            temp[l] = buffer[l];
			            printf("%c", buffer[l]);
			        }
			    }
			    j++;
			 }
			printf("\n\t===========================================================================================================\n");
		    printf("\n\t\t\t\t\t          SURAT KETERANGAN LULUS");
			printf("\n\t\t\t\tPEMINATAN MATEMATIKA DAN ILMU PENGETAHUAN ALAM (MIPA)");
		    printf("\n\t\t\t\t\t         TAHUN PELAJARAN 2020/2021\n\n");
		    printf("\n\t Kepala %s  menerangkan dengan sesungguhnya bahwa:", temp);
		    printf("\n\t\t1. Nama\t\t: %s", data1->nama);
		    printf("\n\t\t2. TTL\t\t: %s", data1->TTL);
		    printf("\n\t\t3. NIS\t\t: %d", data1->NIS);
		    printf("\n\t\t4. NISN\t\t: %d", data1->NISN);
		    printf("\n\t\t5. Kelas\t: %s", data1->kelas);
		    printf("\n\t adalah peserta Ujian Sekolah (US) %s Tahun Pelajaran 2020/2021 dan\n", temp);
		    printf("\n\t berdasarkan ketuntasan dari seluruh program pembelajaran pada kurikulum 2013, kriteria kelulusan\n");
		    printf("\t peserta didik pada satuan %s  yang sesuai dengan peraturan\n", temp);
		    printf("\n\t perundang-undangan dan Hasil Rapat Pleno Dewan Pendidik tentang kelulusan Peserta Didik\n");
		    printf("\t %s  dinyatakan :\n", temp);
		 
			for(k = 0; k<14; k++){
				if(data1->nilai[k]==0){
					printf("\n\t\t\t\t\t\tTIDAK LULUS");
					break;
				}
				else if(data1->nilai[k]>0){
					counter2++;
				}
			}		 
			
			if(counter2==14)
				printf("\n\t\t\t\t\t\t        LULUS");
		 
		    printf("\n\t dengan hasil nilai sebagai berikut : \n");
			printf("\n\t\t\xda\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
			printf("\n\t\t\xb3 No \xb3\t\t\t\t Mata Pelajaran \t\t       \xb3 Nilai Ujian Sekolah \xb3\n");
			printf("\t\t\xc3\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			printf("\n\t\t\xb3   Kelompok A\t\t\t\t\t\t\t       \t\t\t     \xb3");
			printf("\n\t\t\xc3\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			printf("\n\t\t\xb3 1. \xb3\tPendidikan Agama dan Budi Pekerti Luhur\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[0]);
			printf("\n\t\t\xb3 2. \xb3\tPendidikan Pancasila dan Kewarganegaraan\t\t       \xb3\t %d\t     \xb3", data1->nilai[1]);
			printf("\n\t\t\xb3 3. \xb3\tBahasa Indonesia\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[2]);
			printf("\n\t\t\xb3 4. \xb3\tMatematika\t\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[3]);
			printf("\n\t\t\xb3 5. \xb3\tSejarah Indonesia\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[4]);
			printf("\n\t\t\xb3 6. \xb3\tBahasa Inggris\t\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[5]);
			printf("\n\t\t\xc3\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			printf("\n\t\t\xb3   Kelompok B\t\t\t\t\t\t\t       \t\t\t     \xb3");
			printf("\n\t\t\xc3\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			printf("\n\t\t\xb3 7. \xb3\tSeni Budaya\t\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[6]);
			printf("\n\t\t\xb3 8. \xb3\tPendidikan Jasmani, Olahraga, dan Kesehatan\t\t       \xb3\t %d\t     \xb3", data1->nilai[7]);
			printf("\n\t\t\xb3 9. \xb3\tPrakarya dan Kewirausahaan\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[8]);
			printf("\n\t\t\xc3\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			printf("\n\t\t\xb3   Kelompok C\t\t\t\t\t\t\t       \t\t\t     \xb3");
			printf("\n\t\t\xc3\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			printf("\n\t\t\xb3 10.\xb3\tMatematika Lintas Minat\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[9]);
			printf("\n\t\t\xb3 11.\xb3\tBiologi\t\t\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[10]);
			printf("\n\t\t\xb3 12.\xb3\tFisika\t\t\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[11]);
			printf("\n\t\t\xb3 13.\xb3\tKimia\t\t\t\t\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[12]);
			printf("\n\t\t\xb3 14.\xb3\tBahasa dan Sastra Inggris Lintas Minat\t\t\t       \xb3\t %d\t     \xb3", data1->nilai[13]);
			printf("\n\t\t\xc3\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4");
			olah_data(data1->nilai);
			printf("\n\t\t\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
		
		    printf("\n\n\t Surat Keterangan Lulus ini dapat digunakan sebagai pengganti ijazah sampai diterbitkan dokumen ");
		    printf("\n\t ijazah aslinya.");
		    
		    printf("\n\n\t\t\t\t\t\t\t\t\t    ........,..................\n");
			printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t(            			 )");
		}
		data1 = data1->next;

		if(data1 == NULL){
			break;
		}
	}
}
 
int display_panduan(){
    system ("cls");
	printf("\t===================================================================================\n");
    printf("\t\t\t\t\t\tPANDUAN\n");
    printf("\t===================================================================================\n\n");
    printf ("\t Program ini merupakan layanan pembuatan SKL(Surat Keterangan Lulus) untuk siswa.\n");
    printf ("\t Tujuan dari pembuatan program ini akan memudahkan sekolah dalam menyimpan data");
    printf ("\n\t peserta didik serta mencetak SKL.\n");
    printf ("\n\t Pengguna akan memasukkan data berupa:\n\t\t 1.Nama Siswa \n\t\t 2.Tempat Tanggal Lahir ");
    printf ("\n\t\t 3.NIS \n\t\t 4.NISN \n\t\t 5.Kelas \n\t\t 6.Nilai");
    printf ("\n\n\t Kemudian program akan mengolah nilai dengan menampilkan hasil nilai rata-rata");
    printf ("\n\t serta program juga dapat mencetak SKL tersebut.");
    printf ("\n\n\t Silahkan tekan tombol apapun untuk melanjutkan...");
	getch();
}

int keluar(){
    int pil;
	system ("cls");
	printf ("\t\t========================================\n");
    printf ("\t\t\t      MENU KELUAR\n");
    printf ("\t\t========================================\n\n");
	printf ("\n\t\tApakah anda ingin melanjutkan menggunakan program ini?\n\n");
	printf ("\t\t\t1. Ya\n\t\t\t2. Tidak\n\n");
	printf ("\t\tPilihan : ");
	scanf ("%d", &pil);
	
	//Kembali ke menu
	if (pil == 1){
		system("cls");
	}
	//Program berakhir
	else if (pil == 2){
		system("cls");
		printf ("\n\n\t\t\tTerima kasih telah menggunakan program ini!\n");
		exit (0);
	}
	
	//Terdapat default untuk Error Handling apabila User memasukkan pilihan yang salah
	else {
		printf ("\nPilihan yang anda masukkan salah, silahkan coba lagi.\n");
		sleep(1);
		keluar();
	}
}
