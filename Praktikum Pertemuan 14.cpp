#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

// ==========================================
// 1. STRUKTUR KELAS TOKO ELEKTRONIK (OOP)
// ==========================================
class TokoElektronik
{
private:
    array<string, 3> etalase;

public:
    TokoElektronik()
    {
        etalase[0] = "Laptop ASUS ROG";
        etalase[1] = "Smartphone Samsung S24";
        etalase[2] = "Smart TV LG 43 Inch";
    }

    string ambilProduk(size_t nomorRak)
    {
        try
        {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range &)
        {
            throw runtime_error(
                "Gagal Mengambil Barang : Rak nomor [" +
                to_string(nomorRak) +
                "] kosong atau tidak tersedia!");
        }
    }
};

// ==========================================
// 2. FILE I/O DAN CRUD
// ==========================================
const string FILE_NAME = "gudang.txt";

struct Barang
{
    string id;
    string nama;
    string harga;
};

vector<Barang> muatDataGudang()
{
    vector<Barang> daftarBarang;
    ifstream fileInput(FILE_NAME);

    if (!fileInput.is_open())
    {
        ofstream fileBaru(FILE_NAME);
        fileBaru.close();
        return daftarBarang;
    }

    string baris;

    while (getline(fileInput, baris))
    {
        stringstream ss(baris);

        string id, nama, harga;

        if (getline(ss, id, ',') &&
            getline(ss, nama, ',') &&
            getline(ss, harga, ','))
        {

            daftarBarang.push_back({id, nama, harga});
        }
    }

    fileInput.close();
    return daftarBarang;
}

void simpanDataGudang(const vector<Barang> &daftarBarang)
{
    ofstream fileOutput(FILE_NAME, ios::trunc);

    if (fileOutput.is_open())
    {
        for (const auto &b : daftarBarang)
        {
            fileOutput << b.id << ","
                       << b.nama << ","
                       << b.harga << "\n";
        }

        fileOutput.close();
    }
}

void tampilkanGudang()
{
    vector<Barang> daftarBarang = muatDataGudang();

    cout << "\n=============================================\n";
    cout << "      DAFTAR BARANG DI GUDANG (.TXT)\n";
    cout << "=============================================\n";

    if (daftarBarang.empty())
    {
        cout << "[ Gudang Kosong ]\n";
    }
    else
    {
        cout << "ID\t|\tNama Barang\t\t|\tHarga\n";
        cout << "---------------------------------------------\n";

        for (const auto &b : daftarBarang)
        {
            cout << b.id << "\t|\t"
                 << b.nama << "\t\t|\tRp. "
                 << b.harga << "\n";
        }
    }

    cout << "=============================================\n";
}

void tambahBarang()
{
    vector<Barang> daftarBarang = muatDataGudang();
    Barang bBaru;

    cout << "\n--- Tambah Barang Gudang ---\n";
    cout << "Masukkan ID Barang : ";
    cin >> bBaru.id;

    for (const auto &b : daftarBarang)
    {
        if (b.id == bBaru.id)
        {
            cout << "Error: ID sudah digunakan!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Masukkan Nama Barang : ";
    getline(cin, bBaru.nama);

    cout << "Masukkan Harga Barang : ";
    getline(cin, bBaru.harga);

    daftarBarang.push_back(bBaru);

    simpanDataGudang(daftarBarang);

    cout << "Barang berhasil ditambahkan!\n";
}

void updateBarang()
{
    vector<Barang> daftarBarang = muatDataGudang();

    string idCari;
    bool ditemukan = false;

    cout << "\n--- Update Barang ---\n";
    cout << "Masukkan ID Barang : ";
    cin >> idCari;

    for (auto &b : daftarBarang)
    {
        if (b.id == idCari)
        {
            ditemukan = true;

            cin.ignore();

            cout << "Nama Lama : " << b.nama << endl;
            cout << "Harga Lama: " << b.harga << endl;

            cout << "Nama Baru : ";
            getline(cin, b.nama);

            cout << "Harga Baru: ";
            getline(cin, b.harga);

            break;
        }
    }

    if (ditemukan)
    {
        simpanDataGudang(daftarBarang);
        cout << "Data berhasil diperbarui!\n";
    }
    else
    {
        cout << "ID tidak ditemukan!\n";
    }
}

void deleteBarang()
{
    vector<Barang> daftarBarang = muatDataGudang();

    string idCari;
    bool ditemukan = false;

    cout << "\n--- Hapus Barang ---\n";
    cout << "Masukkan ID Barang : ";
    cin >> idCari;

    for (auto it = daftarBarang.begin();
         it != daftarBarang.end();
         ++it)
    {

        if (it->id == idCari)
        {
            daftarBarang.erase(it);
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        simpanDataGudang(daftarBarang);
        cout << "Barang berhasil dihapus!\n";
    }
    else
    {
        cout << "ID tidak ditemukan!\n";
    }
}

void jalankanSimulasiEtalase(TokoElektronik &toko)
{
    cout << "\n=== SIMULASI ETALASE ===\n";

    try
    {
        cout << "Mengambil rak 1...\n";
        cout << toko.ambilProduk(1) << endl;
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }

    try
    {
        cout << "\nMengambil rak 5...\n";
        cout << toko.ambilProduk(5) << endl;
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }
}

int main()
{
    TokoElektronik toko;
    int pilihanMenu;

    do
    {
        tampilkanGudang();

        cout << "\n===== SISTEM TOKO GIBRAN JAYA =====\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Update Barang\n";
        cout << "3. Hapus Barang\n";
        cout << "4. Simulasi Exception\n";
        cout << "5. Keluar\n";
        cout << "Pilih Menu : ";

        if (!(cin >> pilihanMenu))
        {
            cout << "Input harus angka!\n";

            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (pilihanMenu)
        {
        case 1:
            tambahBarang();
            break;

        case 2:
            updateBarang();
            break;

        case 3:
            deleteBarang();
            break;

        case 4:
            jalankanSimulasiEtalase(toko);
            break;

        case 5:
            cout << "Terima kasih.\n";
            break;

        default:
            cout << "Pilihan tidak tersedia.\n";
        }

        if (pilihanMenu != 5)
        {
            cout << "\nTekan Enter...";
            cin.ignore(1000, '\n');
            cin.get();
        }

    } while (pilihanMenu != 5);

    return 0;
}