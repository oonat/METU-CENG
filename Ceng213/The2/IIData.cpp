#include "IIData.hpp"

IIData::IIData() {

}

IIData::IIData(const std::string &word) {

    this->word = word;
}

std::string &IIData::getWord() {

    return word;
}

std::vector<std::pair<std::string, std::vector<int> > > &IIData::getOccurrences() {

    return occurrences;
}

void IIData::setWord(const std::string &word) {

    this->word = word;
}

void IIData::setOccurrences(const std::vector<std::pair<std::string, std::vector<int> > > &occurrences) {

    this->occurrences = occurrences;
}

void IIData::addOccurrence(const std::string &documentName, int position) {
    /* TODO */
    unsigned int i = 0;
    int control = 0;
    std::vector<int> vec;
    vec.push_back(position);
    std::pair<std::string,std::vector<int> > p1(documentName,vec);
    while(i<occurrences.size()){
        if(occurrences[i].first == documentName){
            (occurrences[i].second).push_back(position);
            control = 1;
            break;
        }
        i++;
    }
    
    if(control == 0){
        occurrences.push_back(p1);
    }

}

void IIData::removeOccurrences(const std::string &documentName) {
    /* TODO */
    std::vector<std::pair<std::string,std::vector<int> > >::iterator it = occurrences.begin();
    
    while(it != occurrences.end()){
    	if((*it).first == documentName){
    		occurrences.erase(it);
    		break;
    	}
    	it++;
    }

}

bool IIData::operator<(const IIData &rhs) const {

    return word < rhs.word;
}

bool IIData::operator>(const IIData &rhs) const {

    return word > rhs.word;
}

bool IIData::operator==(const IIData &rhs) const {

    return word == rhs.word;
}

std::ostream &operator<<(std::ostream &os, const IIData &data) {

    os << "{";
    os << "word: " << data.word << ", ";
    os << "occurrences: [";
    for (unsigned int i = 0 ; i < data.occurrences.size() ; ++i) {
        os << "(";
        os << data.occurrences[i].first << ", ";
        os << "[";
        if (!data.occurrences[i].second.empty()) {
            for (unsigned int j = 0 ; j < data.occurrences[i].second.size() - 1; ++j) {
                os << data.occurrences[i].second[j] << ", ";
            }
            os << data.occurrences[i].second[data.occurrences[i].second.size() - 1];
        }
        os << "]";
        os << ")";
        if (i != data.occurrences.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    os << "}";

    return os;
}
