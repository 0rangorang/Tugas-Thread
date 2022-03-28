#include <iostream> 
//standard library input/output stream
#include <thread>
//standard library pemrograman multithreading
#include <mutex>
//standard library mengatur penggunan sebuah resource 
#include <condition_variable>
//standard library isEmpty isFull
#include <chrono>
//standard library sistem tanggal dan waktu 
using namespace std;
//menghapus tulisan std:: di semua fungsi standard library

mutex Mutex;
//mutex berfungsi untuk melindungi variabel/data agar tidak diakses bersamaan oleh banyak thread
//deklarasi variabel mutex yang akan dibawa ke fungsi void
condition_variable Kondis;
//deklarasi variabel yang akan dibawa ke fungsi void
int angka = 1;
// deklarasi variabel angka dan inisialisasi odd number variabel dengan input 1 

void oodThread()
//fungsi yang bernama fungsi void oddThread
{
    for (; angka < 10;)
        //perulangan angka kurang dari 10 
    {
        unique_lock<mutex> manageObj(Mutex);
        //unique_lock, sebuah objek yang mengelola object atau data dari mutex 
        Kondis.wait(manageObj, []() { return (angka % 2 == 1); });
        /*
        ketika variabel Kondis memeriksa penuh atau tidaknya,
        maka akan ada jeda untuk menunggu manageObject mengelola data,
        jika sudah maka akan mereturn hasil loopingan dari inputan variabel angka yaitu angka mod 2 sama dengan 1
        */
        this_thread::sleep_for(chrono::seconds(1));
        //untuk memberikan efek delay selama 1 detik 
        cout << "Odd Thread: " << angka << endl;
        //untuk print Odd Thread sesuai angka yang telah dilooping
        angka++;
        //increment menambah int angka dan masuk ke even number
        Kondis.notify_all();
        //variabel khusus yang mengecek penuh atau tidak (isEmpty isFull).
    }

}

void evenThread()
//fungsi yang bernama fungsi void evenThread
{
    for (; angka < 10;)
        //perulangan angka kurang dari 10 
    {
        unique_lock <mutex> manageObj(Mutex);
        //unique_lock, sebuah objek yang mengelola object atau data dari mutex
        Kondis.wait(manageObj, []() { return (angka % 2 == 0); });
        /*
        ketika variabel Kondis memeriksa penuh atau tidaknya,
        maka akan ada jeda untuk menunggu manageObject mengelola data,
        jika sudah maka akan mereturn hasil loopingan dari inputan variabel angka yaitu angka mod 2 sama dengan 0
        */
        this_thread::sleep_for(chrono::duration<float>(2.5));
        /*untuk memberikan efek delay selama 2.5 detik,
        karena 2.5 bertipe bilangan desimal, maka code yang digunakan ialah float
        */
        cout << "Even Thread: " << angka << endl;
        //untuk print even Thread sesuai angka yang telah dilooping
        angka++;
        //increment menambah int angka dan masuk ke odd number
        manageObj.unlock();
        // pengelolaan data akan terbuka, siap menjadi output
        Kondis.notify_all();
        //variabel khusus yang mengecek penuh atau tidak (isEmpty isFull).
    }
}

int main()
//fungsi utama main 
{
    thread t_ood(oodThread);
    //memanggil fungsi oddThread
    thread t_even(evenThread);
    //memanggil fungsi oddThread
    t_ood.join();
    /*
    .join() adalah method dari thread yang berfungsi untuk mengjoin kan thread ke dalam
    iostream main dan jika tidak pakai ini maka akan error
    */
    t_even.join();
    /*
    .join() adalah method dari thread yang berfungsi untuk mengjoin kan thread ke dalam
    iostream main dan jika tidak pakai ini maka akan error
    */
    cout << endl;
    // untuk merapikan hasil print dengan memisahkannya 1 baris dengan sistem pause dibawah
    system("pause");
    /* untuk konfirmasi kalau sudah selesai, kebiasaan saya saja pak karena ada error di
    di output stream di tugas programming sebelum-sebelumnya dan solusi dari saya dengan ini
    */
    return 0;
    //return biasa
}