#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Buku{
    string kode;
    string judul;
    string pengarang;
    string kategori;
    bool tersedia;
};

struct Peminjam{
    string nama;
    string noperpus;
    string kodeBuku;
    string judulBuku;
};

void simpandatabukukefile(Buku* buku, int totalBuku) {
    ofstream file("daftar_buku.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan data buku!" << endl;
        return;
    }

    for (int i = 0; i < totalBuku; i++) {
        file << buku[i].kode << "|"
             << buku[i].judul << "|"
             << buku[i].pengarang << "|"
             << buku[i].kategori << "|"
             << (buku[i].tersedia ? "1" : "0") << endl;
    }
    file.close();
}

const int Admin_Max = 3;
struct Admin{
    string username;
    int password;
};

Admin data[Admin_Max] = {
    {"sukma", 123137}, {"aulya", 123141}, {"zani", 123148}
};

bool loginRekursif(string username, int password, int indeks = 0) {
    if (indeks >= Admin_Max) {
        return false; // Basis: sudah dicek semua, tapi tidak cocok
    }
    if (data[indeks].username == username && data[indeks].password == password) {
        return true; // Basis: cocok
    }
    return loginRekursif(username, password, indeks + 1); // Rekurens: cek ke elemen berikutnya
}

bool loginAdmin() {
    string username;
    int password;

    cout << "Login Admin\n";
    cout << "Username : "; cin >> username;
    cout << "Password : "; cin >> password;

    if (loginRekursif(username, password)) {
        cout << "Admin " << username << " Berhasil Masuk.\n";
        return true;
    } else {
        cout << "Login Admin Gagal. Username atau Password salah.\n";
        return false;
    }
}

void urutkanBukuKode(Buku buku[], int totalBuku){
    for (int i = 0; i < totalBuku - 1; i++){
        for (int j = 0; j < totalBuku - i - 1; j++) {
            if (buku[j].kode > buku[j + 1].kode) {
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }
}

void urutkanBukuJudul(Buku buku[], int totalBuku){
    for (int i = 0; i < totalBuku - 1; i++) {
        for (int j = 0; j < totalBuku - i - 1; j++) {
            if (buku[j].judul > buku[j + 1].judul) {
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }
}

void tampilkanBuku(Buku* buku, int totalBuku, string kategoridipilih = "") {
    bool kategoribuku = false;
    string urut;

    system("cls");
    cout << "\n===================================\n";
    cout << "       DAFTAR SEMUA BUKU" << endl;
    cout << "===================================\n";
    cout << "Tampilan Daftar Buku Menggunakan Sorting\n";
    cout << "Urutkan Kode Atau Judul (k/j) : "; cin >> urut;

    simpandatabukukefile(buku, totalBuku);

    if (urut == "k") {
        urutkanBukuKode(buku, totalBuku);
    } else if (urut == "j") {
        urutkanBukuJudul(buku, totalBuku);
    } else {
        cout << "Input Tidak Valid!\n";
        return;
    }

    // Header tabel
    cout << string(105, '=')<<endl;
    cout << left;
    cout << setw(12) << "Kode Buku"
         << setw(45) << "Judul Buku"
         << setw(25) << "Nama Pengarang"
         << setw(15) << "Kategori"
         << setw(12) << "Status" << endl;
    cout << setfill('=') << setw(105) << "" << setfill(' ') << endl;

    // Isi tabel
    for (int i = 0; i < totalBuku; i++) {
        if (kategoridipilih == "" || (buku + i)->kategori == kategoridipilih) {
            kategoribuku = true;
            cout << setw(12) << (buku + i)->kode
                 << setw(45) << (buku + i)->judul
                 << setw(25) << (buku + i)->pengarang
                 << setw(15) << (buku + i)->kategori
                 << setw(12) << ((buku + i)->tersedia ? "Tersedia" : "Dipinjam") << endl;
        }
    }

    if (!kategoribuku) {
        cout << "Tidak ada buku dengan kategori tersebut.\n";
    }
}

void cariBukuKode(Buku* buku, int totalBuku){
    string kode;

    cout << "\n========================================" << endl;
    cout << "   RENTANG KODE UNTUK SETIAP KATEGORI" << endl;
    cout << "========================================" << endl;
    cout << "Kategori Fiksi     (mulai dari 001 )" << endl;
    cout << "Kategori Non Fiksi (mulai dari 101)" << endl;
    cout << "========================================\n\n";
    cout << "Masukkan kode buku yang ingin dicari: ";
    cin >> kode;
    bool ditemukan = false;
    for (int i = 0; i < totalBuku; i++){
        if ((buku + i)->kode == kode){
            ditemukan = true;
            cout << "\nJudul Buku \t: " << (buku + i)->judul << endl;
            cout << "Pengarang \t: " << (buku + i)->pengarang << endl;
            cout << "Kategori \t: " << (buku + i)->kategori << endl;
            cout << "Status \t\t: " << ((buku + i)->tersedia ? "Tersedia" : "Dipinjam") << endl;
            break;
        }
    }
    if (!ditemukan){
        cout << "Buku dengan kode " << kode << " tidak ditemukan." << endl;
    }
}

void pinjamBuku(Buku* buku, int totalBuku, Peminjam* peminjam, int* totalPeminjam){
    string nama, noperpus, ketbuku;

    cout << "\n====================" << endl;
    cout << "  PEMINJAMAN BUKU" << endl;
    cout << "====================" << endl << endl;
    cout << "Nama Peminjam          : "; getline(cin, nama);
    cout << "Nomor Perpustakaan     : "; getline(cin, noperpus);
    cout << "Kode atau Judul Buku yang ingin dipinjam : "; getline(cin, ketbuku);

    bool berhasil = false;
    for (int i = 0; i < totalBuku; i++) {
        if (((buku + i)->kode == ketbuku || (buku + i)->judul == ketbuku) && (buku + i)->tersedia) {
            (buku + i)->tersedia = false;

            (peminjam + (*totalPeminjam))->nama = nama;
            (peminjam + (*totalPeminjam))->noperpus = noperpus;
            (peminjam + (*totalPeminjam))->kodeBuku = (buku + i)->kode;
            (peminjam + (*totalPeminjam))->judulBuku = (buku + i)->judul;
            (*totalPeminjam)++;

            simpandatabukukefile(buku, totalBuku);

            cout << "\nBuku berhasil dipinjam." << endl;
            cout << "Judul Buku : " << (buku + i)->judul << endl;
            cout << "Pengarang  : " << (buku + i)->pengarang << endl;
            berhasil = true;
            break;
        }
    }
    if (!berhasil) {
        cout << "Buku tidak tersedia atau tidak ditemukan.\n";
    }
}

void kembalikanBuku(Buku* buku, int totalBuku, Peminjam* peminjam, int* totalPeminjam){
    string nama;
    char jawab;

    cout << "\n====================" << endl;
    cout << "  PENGEMBALIAN BUKU" << endl;
    cout << "====================" << endl;
    cout << "\nNama Peminjam : "; getline(cin, nama);

    bool ditemukan = false;
    for (int i = 0; i < *totalPeminjam; i++){
        if ((peminjam + i)->nama == nama){
            cout << "Nomor Perpustakaan : " << (peminjam + i)->noperpus << endl;
            cout << "Buku yang dipinjam : " << (peminjam + i)->judulBuku << endl;
            cout << "\nIngin mengembalikan buku? (y/n): ";
            cin >> jawab; cin.ignore();
            if (jawab == 'y' || jawab == 'Y'){
                for (int j = 0; j < totalBuku; j++){
                    if ((buku + j)->kode == (peminjam + i)->kodeBuku){
                        (buku + j)->tersedia = true;
                        break;
                    }
                }
                for (int j = i; j < *totalPeminjam - 1; j++){
                    *(peminjam + j) = *(peminjam + j + 1);
                }
                (*totalPeminjam)--;
                cout << "Buku berhasil dikembalikan.\n";
            }
            ditemukan = true;
            simpandatabukukefile(buku, totalBuku);
            break;
        }
    }
    if (!ditemukan) cout << "Data peminjam tidak ditemukan.\n";
}

void tampilkanPeminjam(Peminjam* peminjam, int totalPeminjam){
    cout << "\n=========================" << endl;
    cout << "  DAFTAR PEMINJAM BUKU" << endl;
    cout << "=========================" << endl;

    if (totalPeminjam == 0){
        cout << "\nBelum ada yang meminjam buku." << endl;
    } else {
        for (int i = 0; i < totalPeminjam; i++){
            cout << "\nNama           : " << (peminjam + i)->nama << endl;
            cout << "No Perpustakaan: " << (peminjam + i)->noperpus << endl;
            cout << "Kode Buku      : " << (peminjam + i)->kodeBuku << endl;
            cout << "Judul Buku     : " << (peminjam + i)->judulBuku << endl;
        }
    }
}

void simpanDataPeminjamKeFile(Peminjam* peminjam, int totalPeminjam, const string& namaFile) {
    ofstream file(namaFile);
    if (!file) {
        cerr << "Gagal membuka file untuk menyimpan data peminjaman.\n";
        return;
    }
    for (int i = 0; i < totalPeminjam; ++i) {
        file << peminjam[i].nama << "|"
             << peminjam[i].noperpus << "|"
             << peminjam[i].kodeBuku << "|"
             << peminjam[i].judulBuku << "\n";
    }
    file.close();
}

void bacaDataPeminjamDariFile(Peminjam* peminjam, int* totalPeminjam, const string& namaFile) {
    ifstream file(namaFile);
    if (!file) return;

    string baris;
    while (getline(file, baris)) {
        size_t pos1 = baris.find('|');
        size_t pos2 = baris.find('|', pos1 + 1);
        size_t pos3 = baris.find('|', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;

        peminjam[*totalPeminjam].nama = baris.substr(0, pos1);
        peminjam[*totalPeminjam].noperpus = baris.substr(pos1 + 1, pos2 - pos1 - 1);
        peminjam[*totalPeminjam].kodeBuku = baris.substr(pos2 + 1, pos3 - pos2 - 1);
        peminjam[*totalPeminjam].judulBuku = baris.substr(pos3 + 1);
        (*totalPeminjam)++;
    }
    file.close();
}

void tambahBuku(Buku* buku, int& totalBuku){
    string judul, pengarang, kategori, kodebaru;
    int noterakhir = 0;
    if (!loginAdmin()) {
        cout<<"Login gagal. Tambah buku dibatalkan"<<endl;
        return;
    }

    ofstream file("daftar_buku.txt", ios::app); 
    if (!file.is_open()) {
        cout << "Gagal buka file" << endl;
        return;
    }

    cin.ignore();
    cout << "\n=========================" << endl;
    cout << "      TAMBAH BUKU" << endl;
    cout << "=========================" << endl;
    cout << "Judul Buku (awal kata kapital) : "; getline(cin, judul);
    cout << "Pengarang                      : "; getline(cin, pengarang);
    cout << "Kategori (Fiksi/Non Fiksi)     : "; getline(cin, kategori);

    for (int i = 0; i < totalBuku; i++) {
        if (buku[i].kategori == kategori) {
            int kode = stoi(buku[i].kode);
            if (kode > noterakhir) noterakhir = kode;
        }
    }

    if (kategori == "Fiksi") {
        kodebaru = to_string(noterakhir + 1);
        while (kodebaru.length() < 3) kodebaru = "0" + kodebaru;
    } else if (kategori == "Non Fiksi") {
        if (noterakhir < 100) noterakhir = 100;
        kodebaru = to_string(noterakhir + 1);
    } else {
        cout << "Kategori tidak valid. Gunakan 'Fiksi' atau 'Non Fiksi'.\n";
        return;
    }

    buku[totalBuku].kode = kodebaru;
    buku[totalBuku].judul = judul;
    buku[totalBuku].pengarang = pengarang;
    buku[totalBuku].kategori = kategori;
    buku[totalBuku].tersedia = true;
    totalBuku++;

    file << kodebaru << "|"
         << judul << "|"
         << pengarang << "|"
         << kategori << "|"
         << buku[totalBuku - 1].tersedia << endl;

    file.close();
    cout << "Buku Berhasil Ditambahkan dengan Kode Buku " << kodebaru << endl;
}

void bacaDataBukuDariFile(Buku* buku, int* totalBuku) {
    ifstream file("daftar_buku.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file daftar_buku.txt" << endl;
        return;
    }

    string line;
    *totalBuku = 0;
    

    while (getline(file, line)) {
        stringstream ss(line);
        string tersedia;
        getline(ss, buku[*totalBuku].kode, '|');
        getline(ss, buku[*totalBuku].judul, '|');
        getline(ss, buku[*totalBuku].pengarang, '|');
        getline(ss, buku[*totalBuku].kategori, '|');
        getline(ss, tersedia, '|');
        buku[*totalBuku].tersedia = (tersedia == "1" || tersedia == "true");

        (*totalBuku)++;
    }
    file.close();
}


void tampilkanMenu(){
    system ("cls");
    cout << "+===================================+" << endl;
    cout << "+========= Selamat Datang ==========+" << endl;
    cout << "+======= Sistem Perpustakaan =======+" << endl;
    cout << "+ 1. Tampilkan Daftar Buku          +" << endl;
    cout << "+ 2. Cari Buku Berdasarkan Kode     +" << endl;
    cout << "+ 3. Pinjam Buku                    +" << endl;
    cout << "+ 4. Kembalikan Buku                +" << endl;
    cout << "+ 5. Tampilkan Daftar Peminjaman    +" << endl;
    cout << "+ 6. Tambah Buku (Admin)            +" << endl;
    cout << "+ 7. Keluar                         +" << endl;
    cout << "+===================================+" << endl;
}

int main(){
    Buku buku[100] = {
        {"001", "Laskar Pelangi", "Andrea Hirata", "Fiksi", true},
        {"002", "Gadis Kretek", "Ratih Kumala", "Fiksi", true},
        {"003", "Bumi Manusia", "Pramoedya Ananta Toer", "Fiksi", true},
        {"004", "Bumi", "Tere Liye", "Fiksi", true},
        {"005", "Dilan 1990", "Pidi Baiq", "Fiksi", true},
        {"006", "Daun yang Jatuh Tak Pernah Membenci Angin", "Tere Liye", "Fiksi", true},
        {"007", "Laut Bercerita", "Leila S. Chudori", "Fiksi", true},
        {"008", "Romeo & Juliet", "Shakespeare", "Fiksi", true},
        {"009", "Cantik Itu Luka", "Eka Kurniawan", "Fiksi", true},
        {"010", "Janji", "Tereliye", "Fiksi", true},
        {"011", "Tentang Kamu", "Tereliye", "Fiksi", true},
        {"012", "Hujan", "Tereliye", "Fiksi", true},
        {"013", "Sang Pemimpi", "Andrea Hirata", "Fiksi", true},
        {"014", "Sunset Bersama Rosie", "Tereliye", "Fiksi", true},
        {"015", "Pulang", "Tereliye", "Fiksi", true},
        {"016", "Pulang", "Leila S. Chudori", "Fiksi", true},
        {"101", "Sapiens", "Yuval Noah Harari", "Non Fiksi", true},
        {"102", "Atomic Habits", "James Clear", "Non Fiksi", true},
        {"103", "Filosofi Teras", "Henry Manampiring", "Non Fiksi", true},
        {"104", "The Psychology of Money", "Morgan Housel", "Non Fiksi", true},
        {"105", "Berani Tidak Disukai", "Ichiro Kishimi", "Non Fiksi", true},
        {"106", "How to Win Friends", "Dale Carnegie", "Non Fiksi", true},
        {"107", "Rich Dad Poor Dad", "Robert Kiyosaki", "Non Fiksi", true}
    };

    Peminjam peminjam[100];
    int totalBuku = 23;
    int totalPeminjam = 0;
    int pilihan;
    bacaDataBukuDariFile(buku, &totalBuku);
    bacaDataPeminjamDariFile(peminjam, &totalPeminjam, "Peminjaman.txt");

    do {
        tampilkanMenu();
        cout << "Pilih Menu : ";
        cin >> pilihan; 
        cin.ignore();

        switch (pilihan) {
            case 1: tampilkanBuku(buku, totalBuku); break;
            case 2: cariBukuKode(buku, totalBuku); break;
            case 3: pinjamBuku(buku, totalBuku, peminjam, &totalPeminjam);
                    simpanDataPeminjamKeFile(peminjam, totalPeminjam, "Peminjaman.txt");
                    break;
            case 4: kembalikanBuku(buku, totalBuku, peminjam, &totalPeminjam);
                    simpanDataPeminjamKeFile(peminjam, totalPeminjam, "Peminjaman.txt");
                    break;
            case 5: tampilkanPeminjam(peminjam, totalPeminjam); break;
            case 6: tambahBuku(buku, totalBuku); break;
            case 7: cout << "Terima kasih telah menggunakan sistem perpustakaan.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

        if (pilihan != 7) system("pause");
    } while (pilihan != 7);

    return 0;
}