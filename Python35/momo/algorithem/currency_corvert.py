print('-----------------------project:currency_corvert------------------------------')


#currency_corvert1.0  
def currency_corvert_1():
    

    tm = input('plese input CNY amount')
    
    print('waring, the defalut currency form USD to CNY is 6.77.')

    

    return 'USD amount: {0} $'.format(eval(tm)/6.77)





    


#currency_corvert2.0
def currency_corvert2():
    tm = input('plese enter money amount with label')

    if  tm[-3:] =='USD': 
        tm = eval(tm[:-3])*6.77

        
        print('waring, the defalut currency form USD to CNY  is 6.77.')

        
        
        return 'USD amount: {0} $'.format(tm)
    elif  tm[-3:] =='CNY': 
         
        print('waring, the defalut currency form CNY to USD is 6.77.')

        
        
        return 'CNY amount: {0} CNY'.format(eval(tm[:-3])/6.77)
    else:
        return 'INVALID INPUT(only convert from  CNY to USD or USD to CNY). ' 



#




#3.0
def currency_corvert3():
    while True:
        
        tm = input('plese enter money amount with label')

        if  tm[-3:] =='USD': 
            tm = eval(tm[:-3])*6.77

            print('----------------------------------------------------')
            print('waring, the defalut currency form USD to CNY  is 6.77.')

            
            print()
            print( 'CNY amount: {0} '.format(tm))
            print('----------------------------------------------------')
            i = input('continue?')
            if i == 'yes':
                continue
            elif i=='no':

                break
            else:
                print('----------------------------------------------------')
                print('input yes or no')
                continue
                    
        elif  tm[-3:] =='CNY': 
            print('----------------------------------------------------')
            
            print('waring, the defalut currency form CNY to USD is 6.77.')

            
            print('----------------------------------------------------')
            print('USD amount: {0}$'.format(eval(tm[:-3])/6.77)) 
            print('----------------------------------------------------')
            i = input('continue?')
            if i == 'yes':
                continue
            elif i=='no':

                break
            else:
                print('----------------------------------------------------' )
                print('input yes or no')
                continue
                    

                
        else:
            print('INVALID INPUT(only convert from  CNY to USD or USD to CNY). ') 
            print('----------------------------------------------------' )
            i = input('continue?')
            if i == 'yes':

                continue
            elif i=='no':

                break
            else:
                print('----------------------------------------------------' )
                print('input yes or no')
                continue
    print('---------------------------------------------------------------------')
    return 'EXITED'        
                    
        









if __name__ == "__main__":
    #print(currency_corvert_1())
    #print(currency_corvert2())
    print(currency_corvert3())
 
    