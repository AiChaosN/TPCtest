

// nested-loop join
Join::Join(const std::string& filename1, const std::string& filename2) {
    file1.open(filename1);
    file2.open(filename2);
    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
    }
}

// sort-merge join
bool Join::next() {
    if (file1.is_open() && file2.is_open()) {
        if (currentRecord1.empty() && getline(file1, line1)) {
            currentRecord1 = splitLine(line1, '|');
        }
        if (currentRecord2.empty() && getline(file2, line2)) {
            currentRecord2 = splitLine(line2, '|');
        }
        if (!currentRecord1.empty() && !currentRecord2.empty()) {
            if (currentRecord1[0] == currentRecord2[0]) {
                return true;
            } else if (currentRecord1[0] < currentRecord2[0]) {
                currentRecord1.clear();
            } else {
                currentRecord2.clear();
            }
        }
    }
    return false;
}

const std::vector<std::string>& Join::getCurrentRecord1() const {
    return currentRecord1;
}

const std::vector<std::string>& Join::getCurrentRecord2() const {
    return currentRecord2;
}

Join::~Join() {
    if (file1.is_open()) {
        file1.close();
    }
    if (file2.is_open()) {
        file2.close();
    }
}


// hash-join
// ------
