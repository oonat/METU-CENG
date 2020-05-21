#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}



SoftCopy::SoftCopy(const SoftCopy& rhs) : Book(rhs.ISBN, rhs.price) {
    
    this->startPage = rhs.startPage;
	this->endPage = rhs.endPage;
	this->numberOfPages = rhs.numberOfPages;
	this->pageContent = rhs.pageContent;
	
	if(rhs.firstHalf != NULL){
	   this->firstHalf = new SoftCopy(*(rhs.firstHalf));
	}else{
	    this->firstHalf = NULL;
	}
	
	if(rhs.secondHalf != NULL){
	   this->secondHalf = new SoftCopy(*(rhs.secondHalf));
	}else{
	    this->secondHalf = NULL;
	}
	
	this->next = rhs.next;
    
}


SoftCopy& SoftCopy::operator=(const SoftCopy& rhs){
    
    if(this != &rhs){
        if (firstHalf != NULL)
		delete firstHalf;
	    if (secondHalf != NULL)
		delete secondHalf;
		
		this->ISBN = rhs.ISBN;
		this->price = rhs.price;
        this->startPage = rhs.startPage;
	    this->endPage = rhs.endPage;
	    this->numberOfPages = rhs.numberOfPages;
	    this->pageContent = rhs.pageContent;
	
	    if(rhs.firstHalf != NULL){
	        this->firstHalf = new SoftCopy(*(rhs.firstHalf));
	    }else{
	        this->firstHalf = NULL;
    	}
	
	    if(rhs.secondHalf != NULL){
	        this->secondHalf = new SoftCopy(*(rhs.secondHalf));
	    }else{
	        this->secondHalf = NULL;
	    }
	
	    this->next = rhs.next;
        
    }
    
    return *this;
}



SoftCopy& SoftCopy::operator+(const SoftCopy& rhs) const{
    
	SoftCopy* base_tree = new SoftCopy(*this);

	const SoftCopy* tmp;
	int i;

	for(i = rhs.startPage; i<=rhs.endPage ; i++){
            tmp = &rhs;
            while(true){
                if(tmp->startPage == i && tmp->endPage == i){
                    base_tree->UploadPage(tmp->pageContent, i);
                    break;
                }else{
                    if(tmp->numberOfPages % 2 == 0){
                        if(i<=(tmp->startPage + (tmp->numberOfPages)/2 - 1) && tmp->firstHalf != NULL){
                            tmp = tmp->firstHalf;
                            continue;
                        }else if(i>(tmp->startPage + (tmp->numberOfPages)/2 - 1) && tmp->secondHalf != NULL){
                            tmp = tmp->secondHalf;
                            continue;
                        }else{
                            break;
                        }
                    }else{
                        if(i<=(tmp->startPage + (tmp->numberOfPages)/2) && tmp->firstHalf != NULL){
                            tmp = tmp->firstHalf;
                            continue;
                        }else if(i>(tmp->startPage + (tmp->numberOfPages)/2) && tmp->secondHalf != NULL){
                            tmp = tmp->secondHalf;
                            continue;
                        }else{
                            break;
                        }
                    }
                }
            }
            
            
        }



return *base_tree;
}






Book* SoftCopy::Clone() const{
    return (new SoftCopy(*this));
}

void SoftCopy::Discount(){
    this->price = (this->price)*(0.75);
}



void SoftCopy::UploadPage(string content_param, int page_param){

	if(this->numberOfPages == 1){
		if(this->startPage == page_param && this->endPage == page_param){
			this->pageContent = content_param;
		}
	}else{


    SoftCopy* tmp = this;
    SoftCopy* new_page = new SoftCopy(this->ISBN, this->price, page_param, page_param);
    new_page->pageContent = content_param;
    
    while(true){

        if(tmp->numberOfPages == 2){
        	if(tmp->startPage == page_param){
        		if(tmp->firstHalf == NULL){
        			tmp->firstHalf = new_page;
        			break;
        		}else{
        			tmp->firstHalf->pageContent = content_param;
        			delete new_page;
        			break;
        		}
        	}else if(tmp->endPage == page_param){
        		if(tmp->secondHalf == NULL){
        			tmp->secondHalf = new_page;
        			break;
        		}else{
        			tmp->secondHalf->pageContent = content_param;
        			delete new_page;
        			break;
        		}
        	}else{
        		break;
        	}

		}else if(tmp->numberOfPages == 3){
			if(tmp->endPage == page_param){
				if(tmp->secondHalf == NULL){
        			tmp->secondHalf = new_page;
        			break;
        		}else{
        			tmp->secondHalf->pageContent = content_param;
        			delete new_page;
        			break;
        		}
			}else if(page_param < tmp->endPage && page_param >= tmp->startPage){
				if(tmp->firstHalf == NULL){
					tmp->firstHalf = new SoftCopy(this->ISBN, this->price, tmp->startPage, tmp->startPage + 1);
				}
				tmp = tmp->firstHalf;
				continue;
			}else{
				break;
			}

        }else if(tmp->numberOfPages % 2 == 0){
            if(page_param <= (tmp->startPage + (tmp->numberOfPages)/2 - 1) && page_param >= tmp->startPage){
           		if(tmp->firstHalf == NULL){
           			tmp->firstHalf = new SoftCopy(this->ISBN, this->price, tmp->startPage, tmp->startPage + (tmp->numberOfPages)/2 - 1);
           		}
           		tmp = tmp->firstHalf;
           		continue;
           }else if(page_param > (tmp->startPage + (tmp->numberOfPages)/2 - 1) && page_param <= tmp->endPage){
           		if(tmp->secondHalf == NULL){
           			tmp->secondHalf = new SoftCopy(this->ISBN, this->price, tmp->startPage + (tmp->numberOfPages)/2, tmp->endPage);
           		}
           		tmp = tmp->secondHalf;
           		continue;
           }else{
           		break;
           }

        }else{
        	if(page_param <= (tmp->startPage + (tmp->numberOfPages)/2) && page_param >= tmp->startPage){
           		if(tmp->firstHalf == NULL){
           			tmp->firstHalf = new SoftCopy(this->ISBN, this->price, tmp->startPage, tmp->startPage + (tmp->numberOfPages)/2);
           		}
           		tmp = tmp->firstHalf;
           		continue;
           }else if(page_param > (tmp->startPage + (tmp->numberOfPages)/2) && page_param <= tmp->endPage){
           		if(tmp->secondHalf == NULL){
           			tmp->secondHalf = new SoftCopy(this->ISBN, this->price, tmp->startPage + (tmp->numberOfPages)/2 + 1, tmp->endPage);
           		}
           		tmp = tmp->secondHalf;
           		continue;
           }else{
           		break;
           }          
        }



    }
  }
}





string SoftCopy::Display(int from, int to) const{

    string disp = "";
    int i;
    const SoftCopy* tmp;
    
    if(from <= to){
        
        for(i = from; i <= to; i++){
            tmp = this;

            while(true){

                if(tmp->startPage == i && tmp->endPage == i){
                    disp += tmp->pageContent;
                    disp.push_back('\n');
                    break;
                }else{

                    if(tmp->numberOfPages % 2 == 0){
                        if(i <= (tmp->startPage + (tmp->numberOfPages)/2 - 1) && (i >= tmp->startPage) && tmp->firstHalf != NULL){
                            tmp = tmp->firstHalf;
                            continue;
                        }else if(i > (tmp->startPage + (tmp->numberOfPages)/2 - 1) && (i <= tmp->endPage) && tmp->secondHalf != NULL){
                            tmp = tmp->secondHalf;
                            continue;
                        }else{
                            break;
                        }

                    }else{
                        if(i <= (tmp->startPage + (tmp->numberOfPages)/2) && (i >= tmp->startPage) && tmp->firstHalf != NULL){
                            tmp = tmp->firstHalf;
                            continue;
                        }else if(i > (tmp->startPage + (tmp->numberOfPages)/2) && (i <= tmp->endPage) && tmp->secondHalf != NULL){
                            tmp = tmp->secondHalf;
                            continue;
                        }else{
                            break;
                        }
                    }

                }
            }
            
            
        }
    }
    
    if(disp != ""){
    	if(disp.back() == '\n')
    		disp.pop_back();
    }

    return disp;
}






// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}
