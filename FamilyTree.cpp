#include "FamilyTree.hpp"
#include <stdexcept>
#include <iostream>


//using std::string::compare;
using family::node;
using family::Tree;
using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::invalid_argument;


// global variables
    const static string& great = "great-" ;
    const static string& grand = "grand" ;


Tree::Tree(const string& head) : _root(new node(head)), _size(1) 
{
}
/*
Tree::~Tree(){
    I SAW SOME UNBELIVIBLE THINGS UNDER THE HOOD
    AT THE END OF MAIN FUNCTION AT THE DEMO FILE THIS DESTRUCTOR IS CALLED BY THE COMPILER
    AS MUCH AS IT IS AN EFFICIENT, IT CAUSED TROUBLES

    remove_node(_root);
}
*/
void Tree::remove_node(node* ptr)
{
    //cout << "inside remove_node with " << ptr -> getName() << endl;
    if (ptr != NULL)
    {  
    //    cout << "removed" << ptr -> getName() << endl;
        delete ptr;
        return;
    }
    else
        return;
}

Tree& Tree::addFather(const string &son, const string &father)
{
    if ( getRootByNode() -> getFather() == NULL && getRoot() == son)
    {
        _root->addFather(father);
     //   cout <<  getRoot() << "   THIS IS THE ROOT SO IT SHOULD HAPPEN ONLY ONCE , father as of now : "  << getRootByNode() -> _father ->getName() << endl;
        return *this;
    }
    node* decendant1;
    node* decendant2;
    decendant1 = getRootByNode()->getFather() != NULL ?  binSearch(son, _root->getFather()) : NULL ;
    decendant2 = getRootByNode()->getMother() != NULL ?  binSearch(son, _root->getMother()) : NULL ;
    cout << decendant1->getName() << "," << decendant2->getName() << endl;
    if (decendant1 == NULL  && decendant2 == NULL)
    {
        throw string("DNF");
    }
    else if (( decendant2 -> getName() == son && decendant2->getFather() != NULL) || ( decendant1 -> getName() == son && decendant1->getFather() != NULL) )
    {
        throw string("has father");
    }
    
    
   // if (decendant1->getName() == decendant2->getName() && (decendant2->getFather() == NULL  || decendant1->getFather() == NULL ) )
   else
    {
        if (decendant2->_name == son && decendant2->getFather() == NULL)
        {
        decendant2->addFather(father);
       // cout <<  decendant2->getName() << " , father as of now : "  << decendant2 -> _father ->getName() << endl;
        return *this;
        }
        if (decendant2->_name == son && decendant2->getFather() != NULL)
        {
            throw invalid_argument(" error");
        }
        
        
        else if(decendant1 -> getName() == son)
        {
       //     cout << "    ***********************************************************                                                                          " << decendant1 -> getName() << endl;
            if (decendant1 -> getFather() == NULL)
        {
        decendant1->addFather(father);
      //  cout <<  decendant1->getName() << " , father as of now : "  << decendant1 -> _father ->getName() << endl;
        return *this;
        }
        //else throw has a father
        }
        else if(decendant2 -> getName() == son)
        {
        if (decendant2 -> getFather() != NULL)
        {
        decendant2->addFather(father);
       // cout <<  decendant2->getName() << " , father as of now : "  << decendant2 -> _father ->getName() << endl;
        }
        //else throw has a father
        return *this;
        }
    }

    if (decendant1 == NULL && decendant2 == NULL)
    {
        throw invalid_argument("an error has occured !  " +son +" is not a part of this family !");
    }
    else if ( (decendant1 != NULL && decendant1 -> getMother() != NULL)  && ( decendant2 != NULL && decendant2 -> getMother() != NULL))
    {
        throw invalid_argument("an error has occured !  " +son +" already has a father !");
    }
    try
    {
    if (decendant1 != NULL)
     {
     decendant1 -> addFather(father);
    // cout <<  decendant1 -> getName() << " , father as of now : "  << decendant1 -> getFather() ->getName() << endl;
     return *this;

    }
    else if (decendant2 != NULL)
    {
        decendant2 -> addFather(father);
      //  cout <<  decendant2 -> getName() << " , father as of now : "  << decendant1 -> getFather() ->getName() << endl;
    }
     }catch (const exception& e) {
        cout << e.what() << endl;
    }
    return *this;
}

Tree& Tree::addMother(const string &son, const string &mother)
{
    if ( getRootByNode() -> getMother() == NULL && getRoot() == son)
    {
        _root->addMother(mother);
        //cout << " THIS IS THE ROOT SO IT SHOULD HAPPEN ONLY ONCE , moterther as of now :   " << getRootByNode()->getMother()->getName() << endl;
        return *this;
    }
    node* decendant1;
    node* decendant2;
    decendant1 = getRootByNode()->getMother() != NULL ?  binSearch(son, _root->getMother()) : NULL ;
    decendant2 = getRootByNode()->getFather() != NULL ?  binSearch(son, _root->getFather()) : NULL ;
    cout << decendant1->getName() << "," << decendant2->getName() << endl;
    if (decendant1 == NULL  && decendant2 == NULL)
    {
        throw string("DNF");
    }
    else if (( decendant2 -> getName() == son && decendant2->getMother() != NULL) || ( decendant1 -> getName() == son && decendant1->getMother() != NULL) )
    {
        throw string("has mother");
    }
    else
    {
        if (decendant2->_name == son)
        {
        decendant2->addMother(mother);
       // cout <<  decendant2->getName() << ", mother as of now : "  << decendant2 -> _mother ->getName() << endl;
        }
        else
        {
        decendant1->addMother(mother);
       // cout <<  decendant1->getName() << " , mother as of now : "  << decendant1 -> _mother ->getName() << endl;
        }
        return *this;
    }
    if (decendant1 == NULL && decendant2 == NULL)
    {
        throw invalid_argument("an error has occured !  " +son +" is not a part of this family !");
    }
    else if ( (decendant1 != NULL && decendant1 -> getMother() != NULL)  && ( decendant2 != NULL && decendant2 -> getMother() != NULL))
    {
        throw invalid_argument("an error has occured !  " +son +" already has a mother !");
    }
    try{
    if (decendant1 != NULL) {
     decendant1 -> addMother(mother);
        // cout <<  decendant1 -> getName() << " , mother as of now : "  << decendant1 -> getMother() ->getName() << endl;
         return *this;
    }
    else if (decendant2 != NULL)
    {
        decendant2 -> addMother(mother);
      //  cout <<  decendant2 -> getName() << " , mother as of now : "  << decendant1 -> getMother() ->getName() << endl;
        return *this;
    }
        
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return *this;
}

node* Tree::binSearch(const std::string& name_to_search , node* current){

if (current->thisIs_myName(name_to_search))
{
cout << " binsearch returns now with current node =" << current->getName() << endl;
    return current;
}
if (current->getMother() != NULL) { return binSearch(name_to_search,current->getMother()); }
if (current->getFather() != NULL) { return binSearch(name_to_search,current->getFather()); }
else return search(name_to_search,current->getSon());
}
bool node::thisIs_myName(const string& search_name){
    if (this->getName() == search_name)
    {
        return true;
    } 
    return false;
    }

const string Tree::relation(const string& family_member)
{
    if (_root -> getName() == family_member)
    {
        return "me";
    }
    /*
    if (getRootByNode()->getMother()->getName() == family_member && getRootByNode()->getMother() != NULL)
    {
        return "mother";
    }
    if (getRootByNode()->getFather()->getName() == family_member && getRootByNode()->getFather() != NULL )
    {
        return "father";
    }
    */
    else
    {
        node* ancestor = binSearch(family_member, getRootByNode() ->getMother());
        node* ancestor1 = search(family_member, getRootByNode() -> getMother() ) ;
        node* ancestor2 = binSearch(family_member, getRootByNode() ->getFather() );
        node* ancestor3 = search(family_member, getRootByNode() -> getFather() );
        if (ancestor == NULL)
        {
            return "unrelated" ;
        }
        else
        {
            cout << "im getting tired from you both.  Search =  moter = " <<ancestor1->getName()     <<   ",         search     =    father    "  << ancestor3->getName()   << endl;
            cout << "im getting tired from you both.  binSearch =  mother = " <<ancestor->getName()     <<   ",         binSearch     =    father    "  << ancestor2->getName()   << endl;
            int counter;
            bool suffix = true;
            if (ancestor->getSon()->getMother()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor,0);
              suffix = ancestor->getSon()-> getMother() ->whatIsMySex();
            }
            else if (ancestor->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor,0);
              suffix = ancestor->getSon()->getFather()->whatIsMySex();
            }
            else if (ancestor2->getSon()->getMother()->getName() == family_member)
            {
               counter = countTreeLevel(ancestor2,0);
               suffix = ancestor2->getSon()-> getMother() ->whatIsMySex();
            }
            else if (ancestor2->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor2,0);
              suffix = ancestor2->getSon()->getFather()->whatIsMySex();
            }
            
            else if (ancestor1->getSon()->getMother()->getName() == family_member)
            {
                counter = countTreeLevel(ancestor1,0);
                suffix = ancestor1->getSon()-> getMother() ->whatIsMySex();
            }
            else if (ancestor1->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor1,0);
              suffix = ancestor1->getSon()->getFather()->whatIsMySex();
            }
            else if (ancestor3->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor3,0);
              suffix = ancestor3->getSon()->getFather()->whatIsMySex();
            }
            else if (ancestor3->getSon()->getMother()->getName() == family_member)
            {
                counter = countTreeLevel(ancestor3,0);
                suffix = ancestor3->getSon()-> getMother() ->whatIsMySex();
            }
            else
            {
                return "unrelated";
            }
            
            cout << "counter = " << counter << endl;
            const string& sex = suffix ? "mother" : "father" ;
    if ( counter == 1 )
    { 
        return sex;
    }
    else if ( counter == 2 ) 
    {
         return grand + sex ;
    }
    else
    {
        
        string ans = "";
        
        int diff = counter - 2 ;
        int i = 0;
        for (; i < diff; i++)
        {
            ans.append(great);
        }
            ans.append(grand);
            ans.append(sex);
            return ans;
    }
    }
    }  
return " i got here somehow ";
}

int Tree::countTreeLevel(node* countFromHere,int counter)
{
    if ( countFromHere -> getSon() != NULL )
    {
        counter++;
        return countTreeLevel ( countFromHere -> getSon() , counter );
    }   
    return counter;
}

const string Tree::find(const string &relationship)
{
    if (relationship == "mother" && _root -> getMother() == NULL )
        {
            throw invalid_argument("Mother have not been stated yet for  " + _root->getName());
        }
    if (relationship == "father" && _root -> getFather() == NULL )
        {
            throw invalid_argument("Father have not been stated yet for  " + _root->getName());
        }
    if (  (int( relationship.find("mother") ) == -1 && int( relationship.find("father") ) == -1 ) )
    {
        throw invalid_argument("The tree cannot handle the '"+relationship+"' relation");
    }
    try{
        if (relationship == "mother" && _root -> getMother() != NULL )
        {
            return _root->getMother()->getName();
        }
        else if (relationship == "father" && _root -> getFather() != NULL )
        {
            return _root->getFather()->getName();
        }
        if (int( relationship.find("great")) ==  -1 )
            {
               return find2GensOfRoot(relationship);
            }       
        }catch
        (const exception& e) {
        cout << e.what()  << endl;
    }
            if (  int(relationship.find("great-")) == -1)
            {
                throw invalid_argument("no such thing");
            }
         try{
            const int wanted_level = countFreq("great-", relationship) + 2; // the number of "great-" in the string + 2
            bool sexOfCandidate = int( relationship.find("mother") ) != -1 ? true : false ;
            return   (candidate(sexOfCandidate,wanted_level,_root));
            }catch(const exception& e){
                cout << e.what() << endl;
            }

    return relationship;
}

const string& Tree::find2GensOfRoot(const string &relation)
{
            if ( int (relation.find("mother") ) != -1 )
            {
                if (_root ->getMother()->getMother() != NULL)
                {
                    return _root -> getMother() ->getMother() ->getName();
                }
                else if (_root ->getFather()->getMother() != NULL)
                {
                    return _root -> getFather() ->getMother() ->getName();
                }
                else
                {
                    throw string("No match for "+relation);
                }
                try
                {
                    
                }
                catch(const std::exception& e)
                {
                    cout << e.what() << '\n';
                }
            }
            else if (  int(relation.find("father")) != -1 )
            {
               if (_root ->getMother()->getFather() != NULL)
                {
                    return _root -> getMother() ->getFather() ->getName();
                }
                else if (_root ->getFather()->getFather() != NULL)
                {
                    return _root -> getFather() ->getFather() ->getName();
                }
                else
                {
                    throw string("No match for "+relation);
                }
                try
                {
                    
                }
                catch(const std::exception& e)
                {
                    cout << e.what() << '\n';
                }
                
}
            return relation;
}

void Tree::remove(const string& family_memeber_toRemove){
    /*
    node* temp = search(family_memeber_toRemove,_root);
    if (temp != NULL  ){ cout << " looking for Ruti " << temp->getName() << endl; }
    if (family_memeber_toRemove == _root ->getName())
    {
        throw invalid_argument("deleting root is forbidden");
    }
    if (temp == NULL)
    {
        throw invalid_argument("either removed already or wasn't there on the first place");
    }
    try{
    if (temp -> getFather() != NULL) { remove(temp -> getFather() -> getName()); }
    if (temp -> getMother() != NULL) { remove(temp -> getMother() -> getName()); }
    
    if (temp -> getSon() != NULL && family_memeber_toRemove == temp->getName() )
    {
        remove_node( temp );
        temp -> getSon() -> _father =NULL;
    }
    else if (temp -> getSon() -> getMother() -> getName() == temp -> getName())
    {
        remove_node(temp) ;
        temp -> getSon() -> _mother =NULL;
    }
    } catch (const exception& e){
        cout << e.what() << endl;
    }
    */
    safe_remove(family_memeber_toRemove,_root);
}
void Tree::safe_remove(const string& family_memeber_toRemove,node* relative)
{
    node* temp = search(family_memeber_toRemove,relative);
    //if (temp != NULL  ){  temp->nodeId(); }
    if (family_memeber_toRemove == _root ->getName())
    {
        throw invalid_argument("deleting root is forbidden");
    }
    if (temp == NULL)
    {
        throw invalid_argument("either removed already or wasn't there on the first place");
    }
    try{
    if (temp -> getFather() != NULL) { safe_remove(temp -> getFather() -> getName(),temp->getFather()); }
    if (temp -> getMother() != NULL) { safe_remove(temp -> getMother() -> getName(),temp->getMother() ); }
    
    if (temp -> getSon() != NULL && family_memeber_toRemove == temp->getName() && !temp->whatIsMySex() )
    {
     //   cout << "father                                       " <<temp->getName() << endl;
        remove_node( temp );
        temp -> getSon() -> _father =NULL;
    }
    else if (temp -> getSon() -> getMother() -> getName() == temp -> getName() && temp->whatIsMySex())
    {
     //   cout << "mother                                       " <<temp->getName() << endl;
        remove_node(temp) ;
        temp -> getSon() -> _mother =NULL;
    }
    //else
    //{
    //    cout << "did not realize which sex                                       " <<temp->getName() << endl;
    //}
    
    } catch (const exception& e){
        cout << e.what() << endl;
    }
        temp = find_node(family_memeber_toRemove);
     if (temp != NULL && temp->getName() != family_memeber_toRemove ){
         cout << temp -> getName() << endl;
          throw invalid_argument("either removed already or wasn't there on the first place"); 
          }
     try
     {
         
     }
     catch(const std::exception& e)
     {
         cout << family_memeber_toRemove << e.what() << '\n';
     }
     
}

void Tree::display()
{
    print_node(_root);
    cout << endl;
}

node* Tree::find_node(const string& family_member)
{
        node* ancestor; node* ancestor1; node* ancestor2; node* ancestor3;
        if ( getRootByNode()->getMother() != NULL ) node* ancestor = binSearch(family_member, getRootByNode() ->getMother());
        if ( getRootByNode()->getMother() != NULL ) node* ancestor1 = search(family_member, getRootByNode() -> getMother() ) ;
        if ( getRootByNode()->getMother() != NULL ) node* ancestor2 = binSearch(family_member, getRootByNode() ->getFather() );
        if ( getRootByNode()->getMother() != NULL ) node* ancestor3 = search(family_member, getRootByNode() -> getFather() );
        else
        {
            cout << "im getting tired from you both.  Search =  moter = " <<ancestor1->getName()     <<   ",         search     =    father    "  << ancestor3->getName()   << endl;
            cout << "im getting tired from you both.  binSearch =  mother = " <<ancestor->getName()     <<   ",         binSearch     =    father    "  << ancestor2->getName()   << endl;
            int counter;
            bool suffix = true;
            if (ancestor->getSon()->getMother()->getName() == family_member )
            {
              counter = counter = countTreeLevel(ancestor,0);
              return ancestor->getSon()-> getMother();
            }
            else if (ancestor->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor,0);
              return ancestor->getSon()->getFather();
            }
            else if (ancestor2->getSon()->getMother()->getName() == family_member)
            {
               counter = countTreeLevel(ancestor2,0);
               return ancestor2->getSon()-> getMother();
            }
            else if (ancestor2->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor2,0);
              return ancestor2->getSon()->getFather();
            }
            
            else if (ancestor1->getSon()->getMother()->getName() == family_member)
            {
                counter = countTreeLevel(ancestor1,0);
                return ancestor1->getSon()->getMother();
            }
            else if (ancestor1->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor1,0);
              return ancestor1->getSon()->getFather();
            }
            else if (ancestor3->getSon()->getFather()->getName() == family_member)
            {
              counter = counter = countTreeLevel(ancestor3,0);
              return ancestor3->getSon();
            }
            else if (ancestor3->getSon()->getMother()->getName() == family_member)
            {
                counter = countTreeLevel(ancestor3,0);
                return ancestor3->getSon()-> getMother();
            }
}
            return NULL;
}

void Tree::print_node(node* current)
{
    //current -> nodeId();
    if (current == NULL)
    {
        return;
    } 
    if (current -> getFather() != NULL ){
        print_node(current-> getFather() );
    }
    
    if (current -> getMother() != NULL ) {
        print_node( current -> getMother () );                                    
    }
    cout << current->getName() <<endl;
return;
}

void node::nodeId(){
    cout << "                                        my name is : " <<  this -> getName() << endl;
    if (this-> getFather()!=NULL) cout << "                     MY FATHER my father is : " <<  this -> _father -> getName() << endl;
    if (getMother() != NULL) cout << "                            my mother is : " <<  this -> _mother -> getName() << endl;
    return;

}

//constructor
node::node(const string &name) : _name(name), _myLevel(0) , _father(NULL), _mother(NULL), _origin_son(NULL) {}

node::node(node* _other) : _name(_other->_name), _myLevel(_other->_myLevel) , _father(_other->_father), _mother(_other->_mother), _origin_son(_other->_origin_son) {}


node* node::addMother(const string &mother_name)
{
    this->_mother = new node(mother_name);
    this -> _mother -> _origin_son = this ;
    const int& lev = 1 + this -> getLevel() ;
    this -> _mother -> setLevel(lev);
    return this;
}


node* node::addFather(const string &father_name){
    this->_father = new node(father_name);
    this -> _father -> _origin_son = this;
    const int& lev = 1 + this -> getLevel() ;
    this -> _father -> setLevel(lev);
    return this;
}

const string Tree::candidate(bool sex,const int& wanted_level,node* cand)
{   
    
    /*
    cout << "wanted_level = " << wanted_level << endl;
    cout << "in candidate, checking " << cand -> getName() << endl;
    
    */
   if (wanted_level == 0)
   {
       return cand->getName();
   }
   if (wanted_level < 0)
   {
       throw invalid_argument("no match");
   }
    try
    {
        if ( 0 <= wanted_level && ( cand-> getMother() != NULL || cand -> getFather () != NULL )  )
    {
        if (cand -> getMother() != NULL && cand->goingSomeWhere(wanted_level,cand->getMother()) )
        { return candidate(sex,wanted_level,cand->getMother()); }
        else if (cand -> getFather() != NULL && cand ->goingSomeWhere( wanted_level, cand -> getFather() ) )
        { return candidate(sex,wanted_level,cand->getFather()); }
    }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return "error";
}
bool node::whatIsMySex()
{
    //cout << " every name that goes with this line is a part of WHATISMYSEX func, this time it is =  " << this -> getName() << endl;
    
    if ( this -> getSon() -> getMother() != NULL && this -> getName() == this -> getSon() -> getMother() -> getName() )
    {
        return true;
    }
    else
    {
        return false;
    }
}
const int& node::getLevel()
        {
            return this ->_myLevel ;
        }
void node::setLevel(const int& depth)
        {
        this -> _myLevel = depth;
        }
node *node::find(const string &relation)
{
    return this;
}
bool node::goingSomeWhere(const int& level,node* current)
{
    if (current == NULL)
    {
        return false;
    }
    //cout << current->getName() << ", level= " << current->getLevel() << endl;
    if (current->getLevel() == level)
    {
       return true;
    }
    else if (getLevel() < level)
    {
        /*
        if (getMother() == NULL && getFather() == NULL)
        {
            return false;
        }
        */
        if (getFather() != NULL)
        {
            return goingSomeWhere(level,current->getFather());
        }
        if (getMother() != NULL)
        {
            return goingSomeWhere(level,current->getMother());
        }
    }
    return false;
}

const string& node::getName(){
    return this->_name;
}

node* node::getFather(){
    return this -> _father;
}

node* node::getMother(){
    return this -> _mother;
}
node* node::getSon(){
    return this -> _origin_son;
}


void node::deleteFather(){
        this -> _father = NULL ;
    }
void node::deleteMother(){
    this -> _mother = NULL;
}    


 node* Tree::search(const std::string& decendant,node* current){
     //cout << "in search of  : " << decendant << ",  where current node is : " << current->getName() <<endl;
     if (decendant == current -> getName())   // found you!
     {
         cout << decendant <<"  binSearch  returns " << current->getName() << endl;
         return current;
     }
     /*
     if (current -> getMother() != NULL ) {return search(decendant,current->getMother()) ; }
     if (current -> getMother() != NULL ) {return search(decendant,current->getMother()) ; }
     else {return NULL;}
    */
    
     if (current -> getFather() != NULL)
     {
         return search(decendant,current->getFather());
     }
     if (current -> getMother() != NULL)
     {
         return search(decendant,current->getMother());
     }
      if (current -> getFather() == NULL && current -> getMother() == NULL)
     /*
        poor baby has no parents, and since it's not him in the fist place there is no where to procced
        find a fat lady and tell her to sing , 'cause it's all over ! 
     */
     {
         cout << "answered positive to have no parents at the moment " << current->getName() << endl;
         return current;
     }
     /*
     else if( current -> getFather() != NULL && current -> getMother() == NULL) // only has a father
     {
         if (current -> getFather() -> getName() == decendant) // if the answer is your father
         {
             return current-> getFather();
         }
         else   // we should continue searching over this branch.
         {
             return search(decendant,current -> getFather());
         } 
     }
     */
    /*
     else if (current -> getFather() == NULL && current -> getMother() != NULL) // similarly , has only mother.
     {
         if (current -> getMother() -> getName() == decendant)
         {
             return current-> getMother();
         }
         else
         {
             return search(decendant,current -> getMother());
         }
     }
     */
    
         /*
     else if (current -> getFather() != NULL && current -> getMother() != NULL) // has both parents
     {


         if (current -> getMother() -> getName() == decendant) // if answer is currnet node's mother
         {
             return current-> getMother();
         }
         if (current -> getFather() -> getName() == decendant) // or it's father
         {
             return current-> getFather();
         }
         else
         {
             node* mother_can = search(decendant,current -> getMother()); // search recursively for ma
             node* father_can = search(decendant,current -> getFather()); // search recursively for pa
             if (father_can != NULL && mother_can == NULL) // one expilicit answer , it's daddy
             {
                 return father_can;
             }
             else if (father_can == NULL && mother_can != NULL) // one expilicit answer , it's mommy
             {
                 return mother_can;
             }
             else
             {
                 return NULL; // it's neither of them.
             }
         }
         */
     return NULL;
     }
 
 
 int Tree::countFreq(const string &pat,const string &txt) 
{ 
    int M = pat.length(); 
    int N = txt.length(); 
    int res = 0; 
    
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) 
    {  
        /* For current index i, check for  
           pattern match */
        int j; 
        for (j = 0; j < M; j++) 
            if (txt[i+j] != pat[j]) 
                break; 
   
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
        if (j == M)   
        { 
           res++; 
           j = 0; 
        } 
    } 
    return res; 
}

const std::string& Tree::getRoot(){
    return this->_root->getName();
}
node* Tree::getRootByNode(){
    return _root;
}
