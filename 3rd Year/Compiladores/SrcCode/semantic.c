#include "semantic.h"

symbTable* class;

// display das tabelas (recursivo)
void displayTables(symbTable* currTable){
    if(currTable == NULL) return;

    if(strcmp(currTable->tableType, "Class") == 0){
        printf("===== %s %s Symbol Table =====\n", currTable->tableType, currTable->tableName);
    }else{
        printf("===== %s %s(%s) Symbol Table =====\n", currTable->tableType, currTable->tableName, toString(currTable->tableParamTypes));
    }
    // auxiliar para percorrer as variavies
    stVar* currVar = currTable->varsList;
    while(currVar != NULL){
        if(strcmp(currTable->tableType, "Class") == 0){
            if(!currVar->isMethod){
                printf("%s\t\t%s\n", currVar->varName, currVar->varType);
            }else{
                if(strcmp(currVar->varParam, "param") == 0){
                    printf("%s\t(%s)\t%s\t%s\n", currVar->varName, toString(currVar->varParamTypes), currVar->varType, currVar->varParam);
                }else{
                    printf("%s\t(%s)\t%s\n", currVar->varName, toString(currVar->varParamTypes), currVar->varType);
                }
            }
        }else{
            if(strcmp(currVar->varParam, "param") == 0){
                printf("%s\t\t%s\t%s\n", currVar->varName,  currVar->varType, currVar->varParam);
            }else{
                printf("%s\t\t%s\n", currVar->varName,  currVar->varType);
            }
        }
        currVar = currVar->nextVar;
    }
    printf("\n");
    displayTables(currTable->nextMethod);
}

// faz a tabela da class, recebe o no Program da ast
symbTable* makeTable_Program(asTree* programNode){
    symbTable* classTable = newTable("Class", "", startHeader());
    class = classTable;
    // auxiliar para percorrer os nos filhos
    asTree* currNode = programNode->sonNode;
    while(currNode != NULL){
        // no caso do Id o nodeType vai ser: Id(...), e preciso separar o "Id" do nome do Id
        // nos restantes casos basta aceder a mesma ao type para obter o tipo do no
        char* type = strtok(strdup(currNode->nodeType), "(");

        // =============== Nomes a acrescentar ao titulo da tabela ===============
        if(strcmp(type, "Id") == 0){
            type = strtok(NULL, "(");
            type = strtok(type, ")");
            classTable->tableName = type;
        }
        // =========================== Vars da tabela ============================
        else if(strcmp(type,"MethodDecl") == 0){
            // temos de ir buscar a info do MethodDecl
            symbTable* methodDecl = makeTable_MethodDecl(currNode); // MethodHeader
            if(checkMethod(methodDecl->tableName, ArrayString2ExpArray(methodDecl->tableParamTypes))){
                currNode->isError = true;
            	printf("Line %d, col %ld: Symbol %s(%s) already defined\n",currNode->sonNode->line,currNode->sonNode->col-getCol(currNode->sonNode->sonNode->nextNode), methodDecl->tableName, toString(methodDecl->tableParamTypes));
            }else{
            	addTable(classTable, methodDecl);
            	addVar(classTable, newVar(methodDecl->tableName, methodDecl->tableParamTypes, methodDecl->varsList->varType, "", true));
            }      
        } else if(strcmp(type,"FieldDecl") == 0){
            // temos de ir buscar a info do FieldDecl
            asTree* fieldDeclType = currNode->sonNode;
            asTree* fieldDeclId = fieldDeclType->nextNode;

            char* varName = strtok(strdup(fieldDeclId->nodeType), "(");
            varName = strtok(NULL, "("); varName = strtok(varName, ")");
            char* type = strdup(fieldDeclType->nodeType);
            type[0] = tolower(type[0]); // Int -> int
            if(strcmp(type, "bool") == 0) type = "boolean";
            else if(strcmp(type, "stringArray") == 0) type = "String[]";

            if(checkVarReserved(varName)){
            	printf("Line %d, col %ld: Symbol %s is reserved\n", fieldDeclId->line, fieldDeclId->col-strlen(varName)+1, varName);
            }else if(checkVars(varName)){
            	printf("Line %d, col %ld: Symbol %s already defined\n", fieldDeclId->line, fieldDeclId->col-strlen(varName)+1, varName);
            }else{
            	addVar(classTable, newVar(varName, startHeader(), type, "", false));	
            }
            
        }
        // proxima iteracao
        currNode = currNode->nextNode;
    }

    currNode = programNode->sonNode;

    enterAST(programNode);

    return classTable;
}

// faz a tabela do MethodDecl
symbTable* makeTable_MethodDecl(asTree* MethodDeclNode){
    // filhos do MethodDecl: MethodHeader, MethodBody
    symbTable* methodDecl = newTable("Method", "", startHeader());
    // Infos a obter: Id, ParamTypes (podemos ter mais do que um!!)

    asTree* methodDeclSon = MethodDeclNode->sonNode;
    ArrayString* paramTypes = startHeader(); // aux para guardar os params

    while(methodDeclSon != NULL){
        // e no MethodHeather que estao as infos do MethodDecl

        // ===================================== MethodHeader =====================================
        if(strcmp(methodDeclSon->nodeType, "MethodHeader") == 0){
            asTree* methodHeaderSon = methodDeclSon->sonNode;
            
            // vai percorrer os nodes para poder encontrar as infos
            while(methodHeaderSon!= NULL){
                char* type = strtok(strdup(methodHeaderSon->nodeType), "(");
                // return info
                if(strcmp(type, "Int") == 0 || strcmp(type, "Bool") == 0 || strcmp(type, "Double") == 0 || strcmp(type, "Void") == 0){
                    // acrscentar o return a tabela do MethodDecl
                    type[0] = tolower(type[0]); // Int -> int
                    if(strcmp(type, "bool") == 0){
                        type = "boolean";
                    }
                    addVar(methodDecl, newVar("return", startHeader(), type, "", false));
                    // na tabela da Class este tipo fica na ultima coluna
                    // enqt se faz a tabela da class vamos buscar o primeiro elemento da tabela do MethodDecl, o return
                }else if(strcmp(type, "Id") == 0){
                    type = strtok(NULL, "(");
                    type = strtok(type, ")");
                    methodDecl->tableName = type;
                }

                // ===================================== MethodParams =====================================
                else if(strcmp(type, "MethodParams") == 0){
                    // acrescentar a tabela os parametros
                    // o son e o ParamDecl | os sons do ParamDecl sao as vars
                    asTree* methodParamsSon = methodHeaderSon->sonNode;
                    while (methodParamsSon != NULL){
                        asTree* paramDeclSon = methodParamsSon->sonNode;
                         // vai passar so pelo tipo das vars, qd ha um tipo ha sempre um id a seguir
                        while (paramDeclSon != NULL){
                            // separa o id da var: { Id(var) } -> { Id, var) } -> { var }
                            char* nome = strtok(strdup(paramDeclSon->nextNode->nodeType), "(");
                            nome = strtok(NULL, "("); nome = strtok(nome, ")");
                            // para por em lowecase
                            char* typeAux = strdup(paramDeclSon->nodeType); typeAux[0] = tolower(typeAux[0]);
                            if(strcmp(typeAux, "stringArray") == 0){ // caso seja string
                                typeAux = "String[]";
                            }else if(strcmp(typeAux, "bool") == 0){
                                typeAux = "boolean";
                            }

                            if(checkVarReserved(nome)){
				            	printf("Line %d, col %ld: Symbol %s is reserved\n",paramDeclSon->nextNode->line,paramDeclSon->nextNode->col-strlen(nome)+1,nome);
				            }else if(checkVarsMethods(nome, methodDecl)){
				            	printf("Line %d, col %ld: Symbol %s already defined\n",paramDeclSon->nextNode->line,paramDeclSon->nextNode->col-strlen(nome)+1,nome);
				            }else{
				            	addVar(methodDecl, newVar(nome, startHeader(), typeAux, "param", false));
				            }
 
                            addString(paramTypes, typeAux);
                            
                            paramDeclSon = paramDeclSon->nextNode->nextNode;
                        }
                        methodParamsSon = methodParamsSon->nextNode;
                    }
                }
                methodHeaderSon = methodHeaderSon->nextNode;
            }
            methodDecl->tableParamTypes = paramTypes;
        } 
        methodDeclSon = methodDeclSon->nextNode;
    }
    return methodDecl;
}


bool compareParamTypes(ArrayString* paramTypes, ExpArray* paramTypes2){
    // ve se apenas um deles e vazio
    if(strcmp(paramTypes->string, "") == 0 ^ paramTypes2->expType == _NONE){
        return false;
    }
    while(paramTypes != NULL && paramTypes2 != NULL){
        if(str2type(paramTypes->string) != paramTypes2->expType){
            return false;
        }
        paramTypes = paramTypes->next;
        paramTypes2 = paramTypes2->next;
    }
    if(paramTypes == NULL ^ paramTypes2 == NULL){
        return false;
    }
    return true;
}

bool compareParamTypesUNEXACT(ArrayString* paramTypes, ExpArray* paramTypes2, int *numbExacts){
    // ve se apenas um deles e vazio
    if(strcmp(paramTypes->string, "") == 0 ^ paramTypes2->expType == _NONE){
        *numbExacts = -1;
        return false;
    }
    while(paramTypes != NULL && paramTypes2 != NULL){
        
        if(str2type(paramTypes->string) != paramTypes2->expType){
            if(!((str2type(paramTypes->string) == _REALLIT && paramTypes2->expType == _INTLIT))){
                *numbExacts = -1;
                return false;
            }
        }else{
            *numbExacts += 1;
        }
        paramTypes = paramTypes->next;
        paramTypes2 = paramTypes2->next;
    }
    if(paramTypes == NULL ^ paramTypes2 == NULL){
        *numbExacts = -1;
        return false;
    }
    return true;
}

// procura a tabela do metodo descrito
symbTable* searchMethodTable(char* methodName, ExpArray* methodParamTypes){
    // var que vai percorrer todas as tabelas
    symbTable* currTable = class;
    if(currTable == NULL) return NULL;

    while(currTable != NULL){
        // encontrou o nome
        if(strcmp(methodName, currTable->tableName) == 0){
            // encontrou os mesmo parametros
            if(compareParamTypes(currTable->tableParamTypes, methodParamTypes)){
                return currTable;
            }
        }
        currTable = currTable->nextMethod;
    }
    return NULL;
}

// inicia o processo de atualizar a AST
void enterAST(asTree* root){
    // este no vai circular pelos MethodDecls
    asTree* methodDeclNode = root->sonNode->nextNode;

    while(methodDeclNode != NULL){
        if(strcmp(methodDeclNode->nodeType,"FieldDecl")!= 0){
            if(methodDeclNode == NULL) return;
            asTree* methodHeaderNode = methodDeclNode->sonNode;

            char* methodName = strdup(methodHeaderNode->sonNode->nextNode->nodeType);
            methodName = strtok(methodName, "("); methodName = getId(methodName);

            asTree* methodParamTypes = methodHeaderNode->sonNode->nextNode->nextNode->sonNode;
            ExpArray* ExpParamTypes, *aux;

            if(methodParamTypes != NULL){ 
                ExpParamTypes = startExpArr(str2type(methodParamTypes->sonNode->nodeType));
                aux = ExpParamTypes;
                while(methodParamTypes->nextNode != NULL){
                    aux->next = startExpArr(str2type(methodParamTypes->nextNode->sonNode->nodeType));
                    aux = aux->next;
                    methodParamTypes = methodParamTypes->nextNode;
                }
            }
            else ExpParamTypes = startExpArr(_NONE);

            symbTable* methodTable = searchMethodTable(methodName, ExpParamTypes);
            asTree* methodBodyNode = methodHeaderNode->nextNode;
            if(methodTable != NULL && methodDeclNode->isError == false){
                //upgradeAST(methodBodyNode, methodTable);
                upgradeCalls(methodBodyNode, methodTable);
            }
        }
        methodDeclNode = methodDeclNode->nextNode;
    }
    
}

// upgrade AST
void upgradeAST(asTree* methodBodyNode, symbTable* methodTable){
    // descer um nivel
    asTree* currNode = methodBodyNode->sonNode;
    if(currNode == NULL) return;
    
    while(currNode != NULL){
        // faz os niveis mais baixos primeiro
        upgradeAST(currNode, methodTable);

        char* nodeType = strdup(currNode->nodeType);
        nodeType = strtok(nodeType, "(");

        if(strcmp(nodeType, "Id") == 0){
            checkId(getId(nodeType), currNode, methodTable);
        }else if(strcmp(nodeType,"Call") == 0){
           currNode->expArr->expType = _UNDEF;
           currNode->sonNode->expArr->expType = _UNDEF;
           currNode->sonNode->isMethod = true;
        }else if(strcmp(nodeType, "Assign") == 0){ // e um Assignment
            if(currNode->sonNode!=NULL) currNode->expArr->expType = currNode->sonNode->expArr->expType;
        }else if(strcmp(nodeType, "ParseInt") == 0){ // parseInt
            currNode->expArr->expType = _INTLIT;
        }else if(strcmp(nodeType, "ParseArgs") == 0){ // parseInt
            if(currNode->sonNode!=NULL) currNode->expArr->expType = currNode->sonNode->nextNode->expArr->expType;
        }

        currNode = currNode->nextNode;
    }

}

// faz os calls de maneira diferente pq o java assim quer
void upgradeCalls(asTree* methodBodyNode, symbTable* methodTable){
    // descer um nivel
    asTree* currNode = methodBodyNode->sonNode;
    if(currNode == NULL) return;

    while(currNode != NULL){
        char* nodeType = strdup(currNode->nodeType);
        nodeType = strtok(nodeType, "(");
        // faz os niveis mais baixos primeiro mas tem de ver os ids que sao metodos e tem de acrescentar aas vars as tabelas
        if(strcmp(nodeType,"VarDecl") == 0){
            asTree* idNode = currNode->sonNode->nextNode; 
            idNode->expArr->expType = _NONE;
            char* idName = strdup(currNode->sonNode->nextNode->nodeType);
            idName = strtok(idName, "("); idName = getId(idName);
            if(checkVarReserved(idName)){
                printf("Line %d, col %ld: Symbol %s is reserved\n", idNode->line, idNode->col-strlen(idName)+1,idName);
            }else if(checkVarsMethods(idName, methodTable)){
                printf("Line %d, col %ld: Symbol %s already defined\n",idNode->line, idNode->col-strlen(idName)+1,idName);
            }else{
                addVar(methodTable, newVar(idName, startHeader(), type2str(str2type(currNode->sonNode->nodeType)), "", false));	
            }
        }else if(strcmp(nodeType,"Call") == 0){
            currNode->expArr->expType = _UNDEF;
            currNode->sonNode->expArr->expType = _UNDEF;
            currNode->sonNode->isMethod = true;
        }
        upgradeCalls(currNode, methodTable);


        if(strcmp(nodeType,"Call") == 0){
           	checkCall(currNode, methodTable);
        }if(strcmp(nodeType,"VarDecl") == 0){
            asTree* idNode = currNode->sonNode->nextNode; 
            idNode->expArr->expType = _NONE;
        }else if(strcmp(nodeType, "Id") == 0){
           	char *aux = getId(nodeType);
            checkId(aux, currNode, methodTable);
            checkIdClass(aux, currNode, methodTable);
           	if(currNode->expArr->expType == _UNDEF && !currNode->isMethod && !checkVarReserved(aux)){
            	printf("Line %d, col %ld: Cannot find symbol %s\n", currNode->line, currNode->col-strlen(aux)+1, aux);
            }
        }else if(strcmp(nodeType,"DecLit") == 0){
            currNode->expArr->expType = _INTLIT;
            char *declit = getId(nodeType);
            char *aux2 = concat("",declit);
            int n = count(aux2);
            char *aux;
            aux = strtok(declit, "_");
            char * final = concat("", aux);
        	while(aux != NULL){
        		aux = strtok(NULL, "_");
        		if(aux != NULL){
        			final= concat(final, aux);
                    break;
        		}
        	}
        	checkBounds(final, currNode, aux2,n);
            free(final);
            free(aux2);
            
        }else if(strcmp(nodeType,"RealLit") == 0){
            currNode->expArr->expType = _REALLIT;
            char *declit = getId(nodeType);
            char *aux2 = concat("",declit);
            char *aux;
            aux = strtok(declit, "_");
            char * final = concat("", aux);
        	while(aux != NULL){
        		aux = strtok(NULL, "_");
        		if(aux != NULL){
        			final= concat(final, aux);
                    break;
        		}
        	}

			char* b = strtok(final,"E");
			float base = atof(b); //base 
			b = strtok(NULL, "E");
			if(b != NULL){
                int numbCasas = 0;
                // casos 0.0(...)1
                if(base < 1){
                    while(base < 1){
                        base = base*10;
                        numbCasas++;
                    }
                }else if(base/10 > 1){
                    // casos 1(...)1.(...)
                    while(base/10 > 0){
                        base = base/10;
                        numbCasas--;
                    }
                }
				int exp = atoi(b); // expoente
                exp=exp-numbCasas;
                if(exp < -324){
                    printf("Line %d, col %ld: Number %s out of bounds\n", currNode->line, currNode->col-strlen(aux2)+1, aux2);
                }else if(exp == -324){
                    if(base < 2.5){
                        printf("Line %d, col %ld: Number %s out of bounds\n", currNode->line, currNode->col-strlen(aux2)+1, aux2);
                    }
                }else if(exp > 308){
                    printf("Line %d, col %ld: Number %s out of bounds\n", currNode->line, currNode->col- strlen(aux2)+1, aux2);
                }else if(exp == 308){
                    if(base >= 1.8){
                        printf("Line %d, col %ld: Number %s out of bounds\n", currNode->line, currNode->col-strlen(aux2)+1, aux2);
                    }
                }
				
			}
            free(final);
            free(aux2);
        }else if(strcmp(nodeType,"BoolLit") == 0){
            currNode->expArr->expType = _BOOLLIT;
        }else if(strcmp(nodeType,"ParseArgs") == 0){
            currNode->expArr->expType = _INTLIT;
            if(currNode->sonNode->expArr->expType != _STRARR){
        		if(currNode->sonNode->nextNode == NULL){
        			printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",currNode->sonNode->line,currNode->sonNode->col,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType));
        		}else{
        			printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",currNode->sonNode->line,currNode->col-15,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType),type2str(currNode->sonNode->nextNode->expArr->expType));
        		}
            	
            }else{
                if(currNode->sonNode->nextNode != NULL){
                    if(currNode->sonNode->nextNode->expArr->expType != _INTLIT){
                        printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",currNode->sonNode->line,currNode->col-15,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType),type2str(currNode->sonNode->nextNode->expArr->expType));
                    }
                }
            }
        }else if(strcmp(nodeType,"Minus") == 0){
            currNode->expArr->expType = checkMinusPlus(currNode->sonNode->expArr->expType);
            if(currNode->expArr->expType == _UNDEF){
                printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",currNode->line,currNode->col,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType));
            }
        }else if(strcmp(nodeType,"Plus") == 0){
            currNode->expArr->expType = checkMinusPlus(currNode->sonNode->expArr->expType);
            if(currNode->expArr->expType == _UNDEF){
                printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",currNode->line,currNode->col,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType));
            }
        }else if(strcmp(nodeType,"Add") == 0){
            currNode->expArr->expType = checkNumbSons(currNode);
             checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Assign") == 0){
            currNode->expArr->expType = currNode->sonNode->expArr->expType;
            checkAssignError(currNode, currNode->nodeType);
        }else if(strcmp(nodeType,"Sub") == 0){
            currNode->expArr->expType = checkNumbSons(currNode);
             checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Mul") == 0){
            currNode->expArr->expType = checkNumbSons(currNode);
             checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Div") == 0){
            currNode->expArr->expType = checkNumbSons(currNode);
             checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Mod") == 0){
            currNode->expArr->expType = checkNumbSons(currNode);
            checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"And") == 0){
            currNode->expArr->expType = _BOOLLIT;
            checkBoolsError(currNode,nodeType);
        }else if(strcmp(nodeType,"Or") == 0){
            currNode->expArr->expType = _BOOLLIT;
            checkBoolsError(currNode,nodeType);
        }else if(strcmp(nodeType,"Xor") == 0){
            currNode->expArr->expType = checkBools(currNode, true);
        }else if(strcmp(nodeType,"Eq") == 0){
            currNode->expArr->expType = checkEqls(currNode);
            checkBoolsError(currNode,nodeType);
        }else if(strcmp(nodeType,"Ge") == 0){
            currNode->col -=1;
            currNode->expArr->expType = checkEqls(currNode);
            checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Gt") == 0){
            currNode->expArr->expType = checkEqls(currNode);
            checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Le") == 0){
            currNode->col -=1;
            currNode->expArr->expType = checkEqls(currNode);
            checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Lt") == 0){
            currNode->expArr->expType = checkEqls(currNode);
            checkOperatorError(currNode, nodeType);
        }else if(strcmp(nodeType,"Ne") == 0){
            currNode->expArr->expType = checkEqls(currNode);
            checkBoolsError(currNode,nodeType);
        }else if(strcmp(nodeType,"Not") == 0){
           currNode->expArr->expType = _BOOLLIT;
           if(currNode->sonNode->expArr->expType != _BOOLLIT){
               printf("Line %d, col %d: Operator ! cannot be applied to type %s\n",currNode->sonNode->line,currNode->col,type2str(currNode->sonNode->expArr->expType));
           }
        }else if(strcmp(nodeType,"Length") == 0){
            currNode->expArr->expType = _INTLIT;
            if(currNode->sonNode->expArr->expType != _STRLIT && currNode->sonNode->expArr->expType != _STRARR){
            	printf("Line %d, col %d: Operator %s cannot be applied to type %s\n",currNode->sonNode->line,currNode->sonNode->col+1,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType));
            }
        }else if(strcmp(nodeType,"Lshift") == 0){
            currNode->expArr->expType = shiftss(currNode);
        }else if(strcmp(nodeType,"Rshift") == 0){
            currNode->expArr->expType = shiftss(currNode);
        }else if(strcmp(nodeType,"StrLit") == 0){
            currNode->expArr->expType = _STRLIT;
        }else if(strcmp(nodeType,"Return")== 0){
        	checkReturnError(methodTable, currNode);
        }else if(strcmp(nodeType,"If") == 0){
        	if(currNode->sonNode->expArr->expType != _BOOLLIT){
        		char* aux = type2str(currNode->sonNode->expArr->expType);
        		if(strcmp(aux,"undef")== 0){
        			printf("Line %d, col %d: Incompatible type undef in if statement\n",currNode->sonNode->line,currNode->sonNode->col);
        		}else{
        			printf("Line %d, col %ld: Incompatible type %s in if statement\n",currNode->sonNode->line,currNode->sonNode->col-getCol(currNode->sonNode),aux);
        		}
        		
        	}
        }else if(strcmp(nodeType,"Print") == 0){
            char* aux = type2str(currNode->sonNode->expArr->expType);
            if(strcmp(aux,"undef")== 0){
                printf("Line %d, col %d: Incompatible type undef in System.out.print statement\n",currNode->sonNode->line,currNode->sonNode->col-8);
            }else if(strcmp(aux,"void")== 0){
                printf("Line %d, col %d: Incompatible type void in System.out.print statement\n",currNode->sonNode->line,currNode->sonNode->col);
            }else if(currNode->sonNode->expArr->expType == _STRARR && currNode->sonNode->nextNode == NULL){
                printf("Line %d, col %ld: Incompatible type %s in System.out.print statement\n",currNode->sonNode->line,currNode->sonNode->col-getCol(currNode->sonNode),type2str(currNode->sonNode->expArr->expType));
            }	
        }

        currNode = currNode->nextNode;
    }

}

void checkReturnError(symbTable* methodDecl, asTree* methodBodySon){
	char* type = checkReturnType(methodDecl);
	//printf("%s\n",type);
	if(methodBodySon->sonNode == NULL && str2type(type) != _VOID){
		printf("Line %d, col %d: Incompatible type void in return statement\n",methodBodySon->line, methodBodySon->col-5);
	}else if(methodBodySon->sonNode != NULL){
		if(methodBodySon->sonNode->expArr->expType == _INTLIT && str2type(type) == _REALLIT){
			return;
		}else if(methodBodySon->sonNode->expArr->expType != str2type(type)){
            if(methodBodySon->sonNode->expArr->expType == _UNDEF){
                long int colAux = methodBodySon->sonNode->col;
                if(strcmp(methodBodySon->sonNode->nodeType, "Call") == 0){
                    colAux = colAux-getCol(methodBodySon->sonNode->sonNode);
                }
                printf("Line %d, col %ld: Incompatible type undef in return statement\n",methodBodySon->sonNode->line, colAux); 
            }else{
                printf("Line %d, col %d: Incompatible type %s in return statement\n",methodBodySon->sonNode->line, methodBodySon->col+2,type2str(methodBodySon->sonNode->expArr->expType));
            }
		}else if(strcmp(type,"void")==0){
			printf("Line %d, col %d: Incompatible type void in return statement\n",methodBodySon->line, methodBodySon->col+2);
		}
	}

}

long int getCol(asTree* currNode){
    char* nodeType = strdup(currNode->nodeType);
    nodeType = strtok(nodeType, "(");
    
    if(strcmp(nodeType,"DecLit") ==0){
        return strlen(getId(nodeType))-1;
    }else if(strcmp(nodeType,"RealLit") ==0){
        return strlen(getId(nodeType))-1;
    }else if(strcmp(nodeType,"BoolLit") ==0){
        return strlen(getId(nodeType))-1;
    }else if(strcmp(nodeType,"Id") ==0){
        return strlen(getId(nodeType))-1;
    }else{
        return 1;
    }

}

char* concat(char *s1, char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int count(char *s){
    int res = 0;
    int i;
    for (i=0;i<strlen(s);i++) 
        if(*(s+i) == '_') 
            res++; 
  
    return res; 
} 

void checkBounds(char* declit, asTree* node, char* originalString, int n){
	long int aux = atol(declit);
	if(aux >= 2147483648){
		printf("Line %d, col %ld: Number %s out of bounds\n", node->line, node->col-strlen(declit)+1-n, originalString);
	}else if(aux <= -2147483648){
		printf("Line %d, col %ld: Number %s out of bounds\n", node->line, node->col-strlen(declit)+1-n, originalString);
	}
}

void checkBoolsError(asTree* currNode, char* nodeType){
    asTree* firstSon = currNode->sonNode;
    asTree* secSon = firstSon->nextNode;

    if(firstSon->expArr->expType == _BOOLLIT && secSon->expArr->expType == _BOOLLIT){
        return;
    }else if(firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _INTLIT){
        return;
    }else if(firstSon->expArr->expType == _REALLIT && secSon->expArr->expType == _REALLIT){
    	return;
    }else if(firstSon->expArr->expType == _REALLIT && secSon->expArr->expType == _INTLIT){
    	return;
    }else if(firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _REALLIT){
    	return;
    }else{
        printf("Line %d, col %ld: Operator %s cannot be applied to types %s, %s\n",currNode->line,currNode->col-strlen(node2operator(nodeType))+1,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType),type2str(currNode->sonNode->nextNode->expArr->expType));
    }
}

void checkAssignError(asTree* currNode, char* nodeType){
	if(currNode->sonNode->expArr->expType == _REALLIT && currNode->sonNode->nextNode->expArr->expType == _INTLIT){
		return;
	}else if(currNode->sonNode->expArr->expType != currNode->sonNode->nextNode->expArr->expType){
		if(currNode->sonNode->nextNode->nextNode == NULL){
			printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",currNode->line,currNode->col,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType),type2str(currNode->sonNode->nextNode->expArr->expType));
		}else if(currNode->sonNode->nextNode->sonNode->expArr->expType != currNode->sonNode->nextNode->sonNode->nextNode->expArr->expType){
			printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",currNode->line,currNode->col,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType),type2str(currNode->sonNode->nextNode->expArr->expType));
		}else if(currNode->sonNode->nextNode->sonNode->expArr->expType == _UNDEF || currNode->sonNode->nextNode->sonNode->nextNode->expArr->expType == _UNDEF){
			printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", currNode->line, currNode->col,node2operator(nodeType), type2str(currNode->sonNode->expArr->expType), type2str(currNode->sonNode->nextNode->expArr->expType));
		}  
    }else if(currNode->sonNode->expArr->expType == _STRARR && currNode->sonNode->nextNode->expArr->expType == _STRARR){
		printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",currNode->line,currNode->col,node2operator(nodeType),type2str(currNode->sonNode->expArr->expType),type2str(currNode->sonNode->nextNode->expArr->expType));
    }
}

void checkOperatorError(asTree* currNode, char* nodeType){
    if(currNode->sonNode->expArr->expType == _INTLIT && currNode->sonNode->nextNode->expArr->expType == _INTLIT){
        return;
    }else if(currNode->sonNode->expArr->expType == _REALLIT && currNode->sonNode->nextNode->expArr->expType == _REALLIT){
        return;
    }else if (currNode->sonNode->expArr->expType == _INTLIT && currNode->sonNode->nextNode->expArr->expType == _REALLIT){
        return ;
    }else if (currNode->sonNode->nextNode->expArr->expType == _INTLIT && currNode->sonNode->expArr->expType == _REALLIT){
        return ;
    }
    else{
    	printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n",currNode->line, currNode->col, node2operator(currNode->nodeType),type2str(currNode->sonNode->expArr->expType), type2str(currNode->sonNode->nextNode->expArr->expType));
    }
}

char* node2operator(char* nodeType){
	if(strcmp(nodeType,"Minus") == 0){
        return "-";
    }else if(strcmp(nodeType,"Plus") == 0){
        return "+";
    }else if(strcmp(nodeType,"Add") == 0){
        return "+";
    }else if(strcmp(nodeType,"Assign") == 0){
    	return "=";
    }else if(strcmp(nodeType,"Sub") == 0){
        return "-";
    }else if(strcmp(nodeType,"Mul") == 0){
        return "*";
    }else if(strcmp(nodeType,"Div") == 0){
        return "/";
    }else if(strcmp(nodeType,"Mod") == 0){
        return "%";
    }else if(strcmp(nodeType,"And") == 0){
        return "&&";
    }else if(strcmp(nodeType,"Or") == 0){
        return "||";
    }else if(strcmp(nodeType,"Xor") == 0){
        return "^";
    }else if(strcmp(nodeType,"Eq") == 0){
        return "==";
    }else if(strcmp(nodeType,"Ge") == 0){
        return ">=";
    }else if(strcmp(nodeType,"Gt") == 0){
        return ">";
    }else if(strcmp(nodeType,"Le") == 0){
        return "<=";
    }else if(strcmp(nodeType,"Lt") == 0){
        return "<";
    }else if(strcmp(nodeType,"Ne") == 0){
        return "!=";
    }else if(strcmp(nodeType,"Not") == 0){
       return "!";
    }else if(strcmp(nodeType,"Lshift") == 0){
        return "<<";
    }else if(strcmp(nodeType,"Rshift") == 0){
        return ">>";
    }else if(strcmp(nodeType,"Length") == 0){
    	return ".length";
    }else if(strcmp(nodeType,"ParseArgs")==0){
    	return "Integer.parseInt";
    }
    return "";
}

char* checkReturnType(symbTable* currMethodTable){
	stVar* currVar = currMethodTable->varsList;
	while(currVar != NULL){
		if(strcmp(currVar->varName, "return")==0){
			return currVar->varType;
		}
		currVar = currVar->nextVar;
	}
	return NULL;

}

bool checkVarsMethods(char* varName, symbTable* currMethodTable){
	//Verficar se está na tabela 
	stVar* currVar = currMethodTable->varsList;
	while(currVar != NULL){
		if(strcmp(currVar->varName, varName)==0){
			return true;
		}
		currVar = currVar->nextVar;
	}
	return false;
}

bool checkVarReserved(char* varName){
	if(strcmp(varName,"_") == 0){
		return true;
	}else{
		return false;
	}
}

bool checkMethod(char* methodName, ExpArray* methodParams){
	symbTable* aux = class;

	while(aux != NULL){
		if(strcmp(methodName, aux->tableName) == 0){
			if(compareParamTypes(aux->tableParamTypes, methodParams)){
				return true;
			}
		}
		aux = aux->nextMethod;
	}
	return false;
}

// verifica se o Id foi declarado no metodo onde esta ou se e uma var global
void checkId(char* idName, asTree* currNode, symbTable* methodTable){
    
    // ver no metodo atual
    stVar* currVar = methodTable->varsList;
    while(currVar != NULL){
        // ve se encontrou a var
        if(strcmp(currVar->varName, idName) == 0){
            // nao e metodo
            if(strcmp(currVar->varParamTypes->string, "") == 0){
                currNode->expArr->expType = str2type(currVar->varType);
                return;
            }else{
                currVar->isMethod = true;
            }
        }
        currVar = currVar->nextVar;
    }

    // percorrer a tabela da class
    currVar = class->varsList;
    while(currVar != NULL){
        // ve se encontrou a var
        if(strcmp(currVar->varName, idName) == 0){
            // nao e metodo
            if(strcmp(currVar->varParamTypes->string, "") == 0){
                currNode->expArr->expType = str2type(currVar->varType);
                return;
            }else{
                currVar->isMethod = true;
            }
        }
        currVar = currVar->nextVar;
    }
    currNode->expArr->expType = _UNDEF;
}

void checkIdClass(char* idName, asTree* currNode, symbTable* methodTable){
    
    if(currNode->expArr->expType == _UNDEF){
        // percorrer a tabela da class
        stVar* currVar = class->varsList;
        while(currVar != NULL){
            // ve se encontrou a var
            if(strcmp(currVar->varName, idName) == 0){
                // nao e metodo
                if(!currNode->isMethod){
                    currNode->expArr->expType = str2type(currVar->varType);
                    return;
                }else{
                    currVar->isMethod = true;
                }
            }
            currVar = currVar->nextVar;
        }
    }
}

char* getId(char* nodeType){
    nodeType = strtok(NULL, "(");
    nodeType = strtok(nodeType, ")");
    return nodeType;
}
// check int and reallit stuff
ExpType checkNumbSons(asTree* currNode){
    asTree* firstSon = currNode->sonNode;
    asTree* secSon = firstSon->nextNode;

    if(firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _INTLIT){
        return firstSon->expArr->expType;
    }else if(firstSon->expArr->expType == _REALLIT && secSon->expArr->expType == _REALLIT){
        return firstSon->expArr->expType;
    }else if (firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _REALLIT){
        return secSon->expArr->expType;
    }else if (secSon->expArr->expType == _INTLIT && firstSon->expArr->expType == _REALLIT){
        return firstSon->expArr->expType;
    }
    else return _UNDEF;
}

ExpType checkBools(asTree* currNode, bool isXor){
    asTree* firstSon = currNode->sonNode;
    asTree* secSon = firstSon->nextNode;

    if(firstSon->expArr->expType == _BOOLLIT && secSon->expArr->expType == _BOOLLIT){
        return _BOOLLIT;
    }else if(firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _INTLIT){
        return _INTLIT;
    }else if(firstSon->expArr->expType == _REALLIT && secSon->expArr->expType == _REALLIT){
    	if(!isXor) return _REALLIT;
        else{
        	printf("Line %d, col %d: Operator ^ cannot be applied to types %s, %s\n", currNode->line, currNode->col,type2str(firstSon->expArr->expType),type2str(secSon->expArr->expType ));
        	return _UNDEF;
        }
    }else{
    	return _UNDEF;
    } // mas causa erro
}

ExpType checkMinusPlus(ExpType sonExpType){
    if(sonExpType == _INTLIT || sonExpType == _REALLIT) return sonExpType;
    else{
        return _UNDEF;
    }
    
}

bool checkVars(char* varName){
	//Verficar se está na tabela geral
	stVar* currVar = class->varsList;
	while(currVar != NULL){
		if(strcmp(currVar->varName, varName)==0 && !currVar->isMethod){
			return true;
		}
		currVar = currVar->nextVar;
	}
	return false;
}

ExpType shiftss(asTree* currNode){
    asTree* firstSon = currNode->sonNode;
    asTree* secSon = firstSon->nextNode;

    if(firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _INTLIT){
        return _INTLIT;
    }else return _UNDEF; // mas causa erro
}

ExpType checkEqls(asTree* currNode){
    asTree* firstSon = currNode->sonNode;
    asTree* secSon = firstSon->nextNode;

    if(firstSon->expArr->expType == secSon->expArr->expType){
        return _BOOLLIT;
    }else if((firstSon->expArr->expType == _INTLIT && secSon->expArr->expType == _REALLIT)||(firstSon->expArr->expType == _REALLIT && secSon->expArr->expType == _INTLIT)){
        return _BOOLLIT;
    }else return _BOOLLIT; //mas da erro
}

ExpType checkAssign(ExpType var, ExpType value){
    if(var == value) return var;
    else{
        var = _NONE;
        value = _NONE;
        return _NONE;
    }
}
// aplica o tipo ao Id(method) e a call
void checkCall(asTree* callNode, symbTable* methodTable){
    // primeiro sonNode e um metodo
    asTree* funcNode = callNode->sonNode;
    funcNode->isMethod = true;

    callNode->expArr->expType = _UNDEF;
    funcNode->expArr->expType = _UNDEF;
    // Id do metodo
    char* funcId = strdup(funcNode->nodeType);
    funcId = strtok(funcId, "("); funcId = getId(funcId);
    //percorrer os nextNode e guardar params
    asTree* currArg = funcNode->nextNode;
    ExpArray* argsArr, *aux;
    // cria um array de exp auxiliar
    if(currArg != NULL){
        argsArr = startExpArr(currArg->expArr->expType);
        aux = argsArr;
        while(currArg->nextNode != NULL){
            aux->next = startExpArr(currArg->nextNode->expArr->expType);
            aux = aux->next;
            currArg = currArg->nextNode;
        }
    } 
    else argsArr = startExpArr(_NONE);
    
    //verifica nome da funcao e argumentos na tabela de simbolos
    stVar* currMethod = class->varsList;
    while(currMethod != NULL){
        // encontrou um method com o mesmo nome
        if(strcmp(currMethod->varName, funcId) == 0){
            if(compareParamTypes(currMethod->varParamTypes, argsArr)){
                callNode->expArr->expType = str2type(currMethod->varType);
                funcNode->expArr = argsArr;
                return;
            }
        }
        currMethod = currMethod->nextVar;
    }

    currMethod = class->varsList;
    int numbExact = 0, biggestExact = -1;
    while(currMethod != NULL){
        numbExact = 0;
        // encontrou um method com o mesmo nome
        if(strcmp(currMethod->varName, funcId) == 0){
            if(compareParamTypesUNEXACT(currMethod->varParamTypes, argsArr, &numbExact)){
                if(numbExact >= biggestExact){
                    if(numbExact == biggestExact){
                        callNode->expArr->expType = _UNDEF;
                        free(funcNode->expArr->next);
                        funcNode->expArr->next = NULL;
                        funcNode->expArr->expType = _UNDEF;
                    }else{
                        biggestExact = numbExact;
                        callNode->expArr->expType = str2type(currMethod->varType);
                        funcNode->expArr = ArrayString2ExpArray(currMethod->varParamTypes);
                    }
                }
            }
        }
        currMethod = currMethod->nextVar;
    }

    if(callNode->expArr->expType == _UNDEF){
    	char* aux = type2finalString(argsArr);
        if(numbExact == biggestExact){
            printf("Line %d, col %ld: Reference to method %s(%s) is ambiguous\n", funcNode->line, callNode->col-strlen(funcId)+1, funcId, aux);
        }
        else printf("Line %d, col %ld: Cannot find symbol %s(%s)\n", funcNode->line, callNode->col-strlen(funcId)+1, funcId, aux);
    }/*else{
        char* aux = type2finalString(argsArr);
        if(biggestExact > -1){
            printf("Line %d, col %ld: Reference to method %s(%s) is ambiguous\n", funcNode->line, callNode->col-strlen(funcId)+1, funcId, aux);
        }
    }*/
}

ExpArray* ArrayString2ExpArray(ArrayString* arrStr){
    ExpArray* copy = startExpArr(_NONE);
    ExpArray* returnCopy = copy;
    copy->expType = str2type(arrStr->string);
    copy->next = startExpArr(_NONE);
    while(arrStr->next != NULL){
        copy->next->expType = str2type(arrStr->next->string);
        copy->next->next = startExpArr(_NONE);
        copy = copy->next;
        arrStr = arrStr->next;
    }
    free(copy->next);
    copy->next = NULL;
    return returnCopy;
}