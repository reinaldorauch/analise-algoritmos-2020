use rand::Rng;

const RUN: usize = 32;

fn insertion_sort(v: &mut Vec<i64>, min: usize, max: usize) {
    let mut copy = Vec::with_capacity(RUN);
    copy.clone_from_slice(v);

}

fn timsort(v: &mut Vec<i64>) {
    let mut i = 0;
    while i < v.size() {
        insertion_sort()
        i += RUN ;
    }
}

fn make_random_vec(n: usize) -> Vec<i64> {
    let mut v: Vec<i64> = Vec::with_capacity(n);
    let mut rng = rand::thread_rng();

    let mut i: usize = 0;

    while i < n {
        v.push(rng.gen());
        i += 1;
    }

    v
}

fn main() {
    let mut v = make_random_vec(10000);
    println!("vector {:?}", v);
    timsort(&v);
    println!("vector {:?}", v);
}
