#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Batas maksimum jumlah karyawan
const int MAX_KARYAWAN = 200;

// Struktur data karyawan
struct Karyawan {
    string nama;
    int id;
    int gajiPokok, gajiLembur, pajak, gajiTotal;
    string nohp;
    string jabatan;
    string alamat;
};

// Informasi gaji
void infoGajiKaryawan() {
    cout << "+------------------------------------------+" << endl;
    cout << "|   JABATAN   |    GAJI    |     PAJAK     |" << endl;
    cout << "+------------------------------------------+" << endl;
    cout << "|BENDAHARA    |   100000   |      02%      |" << endl;
    cout << "+------------------------------------------+" << endl;
    cout << "|SEKERTARIS   |   100000   |      02%      |" << endl;
    cout << "+------------------------------------------+" << endl;
}

// Fungsi untuk menginput data karyawan
void inputDataKaryawan(Karyawan& karyawan, const Karyawan daftarKaryawan[], int jumlahKaryawan) {
    cout << "Masukkan Nama\t\t  : ";
    getline(cin, karyawan.nama);

    bool idValid = false;
    while (!idValid) {
        cout << "Masukkan ID\t\t  : ";
        cin >> karyawan.id;
        cin.ignore();

        // Memeriksa apakah ID sudah digunakan sebelumnya
        bool idUsed = false;
        for (int i = 0; i < jumlahKaryawan; i++) {
            if (daftarKaryawan[i].id == karyawan.id) {
                idUsed = true;
                break;
            }
        }

        if (idUsed) {
        	cout << "+------------------------+" << endl;
            cout << "| ID TELAH DIGUNAKAN !!! |" << endl;
            cout << "+------------------------+" << endl;
        } else {
            idValid = true;
        }
    }

    cout << "Masukkan No. HP\t\t  : ";
    getline(cin, karyawan.nohp);
    cout << "Masukkan Jabatan\t  : ";
    getline(cin, karyawan.jabatan);
    cout << "Masukkan Alamat\t\t  : ";
    getline(cin, karyawan.alamat);
}

// Fungsi untuk menghitung gaji pokok
int hitungGajiPokok(int HariKerja) {
    return HariKerja * 100000;
}

// Fungsi untuk menghitung gaji lembur
int hitungGajiLembur(int jamLembur) {
    return jamLembur * 50000;
}

// Fungsi untuk menghitung pajak
int hitungPajak(float gajiTotal) {
    return gajiTotal * 0.1;
}

// Fungsi untuk mencari indeks data karyawan berdasarkan ID
int cariIndeksKaryawan(const Karyawan daftarKaryawan[], int jumlahKaryawan, int id) {
    for (int i = 0; i < jumlahKaryawan; i++) {
        if (daftarKaryawan[i].id == id) {
            return i;  // Mengembalikan indeks data karyawan jika ditemukan
        }
    }
    return -1;  // Mengembalikan -1 jika data karyawan tidak ditemukan
}

// Fungsi untuk menghapus data karyawan berdasarkan ID
void hapusDataKaryawan(Karyawan daftarKaryawan[], int& jumlahKaryawan, int id) {
    int indeks = cariIndeksKaryawan(daftarKaryawan, jumlahKaryawan, id);
    if (indeks != -1) {
        // Menggeser data ke kiri untuk menutupi data yang dihapus
        for (int i = indeks; i < jumlahKaryawan - 1; i++) {
            daftarKaryawan[i] = daftarKaryawan[i + 1];
        }
        jumlahKaryawan--;
        cout << "\nData karyawan dengan ID " << id << " berhasil dihapus." << endl;
    } else {
        cout << "Data karyawan dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void simpanDataKaryawan(const Karyawan daftarKaryawan[], int jumlahKaryawan) {
    ofstream file("data_karyawan.txt", ios::app);  // Menggunakan mode append agar data tidak dihapus saat program ditutup

    if (file.is_open()) {
        for (int i = 0; i < jumlahKaryawan; i++) {
            file << daftarKaryawan[i].nama << endl;
            file << daftarKaryawan[i].id << endl;
            file << daftarKaryawan[i].gajiPokok << endl;
            file << daftarKaryawan[i].gajiLembur << endl;
            file << daftarKaryawan[i].pajak << endl;
            file << daftarKaryawan[i].gajiTotal << endl;
            file << daftarKaryawan[i].nohp << endl;
            file << daftarKaryawan[i].jabatan << endl;
            file << daftarKaryawan[i].alamat << endl;
        }
        file.close();
        cout << "Data karyawan berhasil disimpan." << endl;
    } else {
        cout << "Gagal menyimpan data karyawan." << endl;
    }
}

void muatDataKaryawan(Karyawan daftarKaryawan[], int& jumlahKaryawan) {
    ifstream file("data_karyawan.txt");

    if (file.is_open()) {
        string line;
        int count = 0;
        while (getline(file, line)) {
            daftarKaryawan[count].nama = line;
            file >> daftarKaryawan[count].id;
            file >> daftarKaryawan[count].gajiPokok;
            file >> daftarKaryawan[count].gajiLembur;
            file >> daftarKaryawan[count].pajak;
            file >> daftarKaryawan[count].gajiTotal;
            file.ignore();
            getline(file, daftarKaryawan[count].nohp);
            getline(file, daftarKaryawan[count].jabatan);
            getline(file, daftarKaryawan[count].alamat);
            count++;
        }
        jumlahKaryawan = count;
        file.close();
        cout << "Data karyawan berhasil dimuat." << endl;
    } else {
        cout << "Gagal memuat data karyawan." << endl;
    }
}


int main() {
    Karyawan daftarKaryawan[MAX_KARYAWAN]; // Array of structs untuk menyimpan data karyawan
    int jumlahKaryawan = 0; // Jumlah karyawan yang saat ini disimpan

    int pilihan;

    do {
    	cout << "+----------------------------------------------+\n";
    	cout << "|                   STAFFHUB                   |\n";
    	cout << "+----------------------------------------------+\n";
        cout << "|       Sistem Pengelolaan Data Karyawan       |\n";
        cout << "+----------------------------------------------+\n";
        cout << "|          1. Informasi Gaji Karyawan          |\n";
        cout << "|          2. Input Data Karyawan              |\n";        
        cout << "|          3. Tampilkan Data Karyawan          |\n";
        cout << "|          4. Cari Data Karyawan               |\n";
        cout << "|          5. Hapus Data Karyawan              |\n";
        cout << "|          6. Simpan Data Karyawan             |\n";
    	cout << "|          7. Memuat Data Karyawan             |\n";
        cout << "|          8. Exit                             |\n";
        cout << "+----------------------------------------------+\n";

        cout << "\n\t\t Pilih Menu: ";
		cin >> pilihan;
        cin.ignore();
        system("cls");

        switch (pilihan) {
            case 1:
                // Menampilkan informasi gaji karyawan
                infoGajiKaryawan();
                cout << endl;
                system("pause");
                system("cls");
                break;
            case 2: {
                // Input data karyawan
                if (jumlahKaryawan < MAX_KARYAWAN) {
                    Karyawan karyawan;
					inputDataKaryawan(karyawan, daftarKaryawan, jumlahKaryawan);


                    // Input hari kerja
                    int HariKerja;
                    cout << "Masukkan Jumlah Hari Kerja: ";
                    cin >> HariKerja;

                    // Input data lembur
                    int jamLembur;
                    cout << "Masukkan Jumlah Jam Lembur: ";
                    cin >> jamLembur;

                    // Menghitung gaji pokok
                    int gajiPokok = hitungGajiPokok(HariKerja);

                    // Menghitung gaji lembur
                    int gajiLembur = hitungGajiLembur(jamLembur);

                    // Menghitung gaji total
                    int gajiTotal = gajiPokok + gajiLembur;

                    // Menghitung pajak
                    int pajak = hitungPajak(gajiTotal);

                    // Menyimpan data perhitungan gaji pada struktur karyawan
                    karyawan.gajiPokok = gajiPokok;
                    karyawan.gajiLembur = gajiLembur;
                    karyawan.pajak = pajak;
                    karyawan.gajiTotal = gajiTotal - pajak;

                    // Menyimpan data karyawan ke array
                    daftarKaryawan[jumlahKaryawan] = karyawan;
                    jumlahKaryawan++;

                    // Menampilkan hasil perhitungan
                    cout << endl;
                    cout << "-----------------------------------------------------------+\n";
                    cout << "            Hasil Perhitungan Gaji                         |\n";
    				cout << "-----------------------------------------------------------+\n";
                    cout << "\tNama\t\t: " << karyawan.nama << "\n";
                    cout << "\tID\t\t: " << karyawan.id << "\n";
                    cout << "\tNo. HP\t\t: " << karyawan.nohp << "\n";
                    cout << "\tJabatan\t\t: " << karyawan.jabatan << "\n";
                    cout << "\tAlamat\t\t: " << karyawan.alamat << "\n";
                    cout << "\tGaji Pokok\t: Rp " << karyawan.gajiPokok << "\n";
                    cout << "\tGaji Lembur\t: Rp " << karyawan.gajiLembur << "\n";
                    cout << "\tPajak\t\t: Rp " << karyawan.pajak << "\n";
                    cout << "\tGaji Total\t: Rp " << karyawan.gajiTotal << "\n";
                    cout << "------------------------------------------------------------\n";

                    cout << endl;
                    system("pause");
                    system("cls");
                } else {
                    cout << "Karyawan sudah mencapai batas maksimum." << endl;
                    cout << endl;
                    system("pause");
                    system("cls");
                }
                break;
            }
            case 3:
                if (jumlahKaryawan > 0) {
                    for (int i = 0; i < jumlahKaryawan; i++) {
                        cout << "Data Karyawan\t: " << i + 1 << endl;
                        cout << "Nama\t\t: " << daftarKaryawan[i].nama << endl;
                        cout << "ID\t\t: " << daftarKaryawan[i].id << endl;
                        cout << "No. HP\t\t: " << daftarKaryawan[i].nohp << endl;
                        cout << "Jabatan\t\t: " << daftarKaryawan[i].jabatan << endl;
                        cout << "Alamat\t\t: " << daftarKaryawan[i].alamat << endl;
                        cout << "Gaji Pokok\t: Rp " << daftarKaryawan[i].gajiPokok << endl;
                        cout << "Gaji Lembur\t: Rp " << daftarKaryawan[i].gajiLembur << endl;
                        cout << "Pajak\t\t: Rp " << daftarKaryawan[i].pajak << endl;
                        cout << "Gaji Total\t: Rp " << daftarKaryawan[i].gajiTotal << endl;
                        cout << "============================================================\n";
                    }
                } else {
                    cout << "Data karyawan kosong." << endl;
                }
                cout << endl;
                system("pause");
                system("cls");
                break;
            case 4: {
                // Cari data karyawan berdasarkan ID
                int cariID;
                cout << "Masukkan ID karyawan yang dicari: ";
                cin >> cariID;
                cout << endl;

                bool ditemukan = false;
                for (int i = 0; i < jumlahKaryawan; i++) {
                    if (daftarKaryawan[i].id == cariID) {
                    	cout << "============================================================\n";
                        cout << "Data Karyawan\t: " << i + 1 << endl;
                        cout << "Nama\t\t: " << daftarKaryawan[i].nama << endl;
                        cout << "ID\t\t: " << daftarKaryawan[i].id << endl;
                        cout << "No. HP\t\t: " << daftarKaryawan[i].nohp << endl;
                        cout << "Jabatan\t\t: " << daftarKaryawan[i].jabatan << endl;
                        cout << "Alamat\t\t: " << daftarKaryawan[i].alamat << endl;
                        cout << "Gaji Pokok\t: Rp " << daftarKaryawan[i].gajiPokok << endl;
                        cout << "Gaji Lembur\t: Rp " << daftarKaryawan[i].gajiLembur << endl;
                        cout << "Pajak\t\t: Rp " << daftarKaryawan[i].pajak << endl;
                        cout << "Gaji Total\t: Rp " << daftarKaryawan[i].gajiTotal << endl;
                        cout << "============================================================\n";

                        ditemukan = true;
                        break;
                    }
                }
				
				 if (ditemukan) {
                    cout << "Data Karyawan dengan ID " << cariID << "\nditemukan." << endl;
                }
                else if (!ditemukan) {
                    cout << "Data Karyawan dengan ID " << cariID << " tidak ditemukan." << endl;
                }

                cout << endl;
                system("pause");
                system("cls");
                break;
            }
            case 5: {
                // Hapus data karyawan berdasarkan ID
                int id;
                cout << "Masukkan ID karyawan yang akan dihapus: ";
                cin >> id;

                hapusDataKaryawan(daftarKaryawan, jumlahKaryawan, id);

                cout << endl;
                system("pause");
                system("cls");
                break;
            }
			case 6: {
			    if (jumlahKaryawan > 0) {
			        simpanDataKaryawan(daftarKaryawan, jumlahKaryawan);
			    } else {
			        cout << "Data karyawan kosong." << endl;
			    }
			    cout << endl;
			    system("pause");
			    system("cls");
			    break;
			}
			case 7: {
			    muatDataKaryawan(daftarKaryawan, jumlahKaryawan);
			    cout << endl;
			    system("pause");
			    system("cls");
			    break;
			}
            case 8:
                // keluar dari program
                cout << "Terima kasih:)" << endl;
                break;
            default:
                cout << "Pilihan tidak valid;(" << endl;
                cout << endl;
                system("pause");
                system("cls");
                break;
        }
    } while (pilihan != 8);
    
    return 0;
}
