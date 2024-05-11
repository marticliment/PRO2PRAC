#include <iostream>
#include "RiverArray.hh"
#include "debug.hh"

using namespace std;

const string LEER_RIO = "lr";
const string LEER_RIO_L = "leer_rio";
const string LEER_INVENTARIO = "li";
const string LEER_INVENTARIO_L = "leer_inventario";
const string LEER_INVENTARIOS = "ls";
const string LEER_INVENTARIOS_L = "leer_inventarios";
const string MODIFICAR_BARCO = "mb";
const string MODIFICAR_BARCO_L = "modificar_barco";
const string ESCRIBIR_BARCO = "eb";
const string ESCRIBIR_BARCO_L = "escribir_barco";
const string CONSULTAR_NUM = "cn";
const string CONSULTAR_NUM_L = "consultar_num";
const string AGREGAR_PRODUCTOS = "ap";
const string AGREGAR_PRODUCTOS_L = "agregar_productos";
const string ESCRIBIR_PRODUCTO = "ep";
const string ESCRIBIR_PRODUCTO_L = "escribir_producto";
const string ESCRIBIR_CIUDAD = "ec";
const string ESCRIBIR_CIUDAD_L = "escribir_ciudad";
const string PONER_PROD = "pp";
const string PONER_PROD_L = "poner_prod";
const string MODIFICAR_PROD = "mp";
const string MODIFICAR_PROD_L = "modificar_prod";
const string QUITAR_PROD = "qp";
const string QUITAR_PROD_L = "quitar_prod";
const string CONSULTAR_PROD = "cp";
const string CONSULTAR_PROD_L = "consultar_prod";
const string COMERCIAR = "co";
const string COMERCIAR_L = "comerciar";
const string REDISTRIBUIR = "re";
const string REDISTRIBUIR_L = "redistribuir";
const string HACER_VIAJE = "hv";
const string HACER_VIAJE_L = "hacer_viaje";
const string FIN = "fin";


void PrintCommand(string c)
{
#ifdef DEBUG
    cout << green << "#" + c << reset << endl;
#else
    cout << "#" + c << endl;
#endif
}


/// @brief Entry point of the program
int main()
{
    Log("Begin initializing river");
    RiverArray mainMap;
    mainMap.InitializeFromStream(cin);
    Log("Finished initializing RiverArray, reaching main loop");
    string c;
    while(cin >> c && c != FIN)
    {
        if(c != "//") PrintCommand(c);
        
        if(c == LEER_RIO || c == LEER_RIO_L)
        {
            Log("Operation LEER_RIO not implemented yet");
        }
        else if(c == LEER_INVENTARIO || c == LEER_INVENTARIO_L)
        {
            Log("Operation LEER_INVENTARIO not implemented yet");
        }
        else if(c == LEER_INVENTARIOS || c == LEER_INVENTARIOS_L)
        {
            Log("Operation LEER_INVENTARIOS not implemented yet");
        }
        else if(c == MODIFICAR_BARCO || c == MODIFICAR_BARCO_L)
        {
            Log("Operation MODIFICAR_BARCO not implemented yet");
        }
        else if(c == ESCRIBIR_BARCO || c == ESCRIBIR_BARCO_L)
        {
            Product& buying = mainMap.GetShip().BuyingProduct();
            Product& selling = mainMap.GetShip().SellingProduct();
            // TODO: Check if GetMissingAmount or GetRequiredAmount
            cout << buying.GetId() << ' ' << buying.GetMissingAmount() << ' ';
            cout << selling.GetId() << ' ' << selling.GetCurrentAmount() << endl;
        }
        else if(c == CONSULTAR_NUM || c == CONSULTAR_NUM_L)
        {
            Log("Operation CONSULTAR_NUM not implemented yet");
        }
        else if(c == AGREGAR_PRODUCTOS || c == AGREGAR_PRODUCTOS_L)
        {
            Log("Operation AGREGAR_PRODUCTOS not implemented yet");
        }
        else if(c == ESCRIBIR_CIUDAD || c == ESCRIBIR_CIUDAD_L)
        {
            Log("Operation ESCRIBIR_CIUDAD not implemented yet");
        }
        else if(c == PONER_PROD || c == PONER_PROD_L)
        {
            Log("Operation PONER_PROD not implemented yet");
        }
        else if(c == MODIFICAR_PROD || c == MODIFICAR_PROD_L)
        {
            Log("Operation MODIFICAR_PROD not implemented yet");
        }
        else if(c == QUITAR_PROD || c == QUITAR_PROD_L)
        {
            Log("Operation QUITAR_PROD not implemented yet");
        }
        else if(c == CONSULTAR_PROD || c == CONSULTAR_PROD_L)
        {
            Log("Operation CONSULTAR_PROD not implemented yet");
        }
        else if(c == COMERCIAR || c == COMERCIAR_L)
        {
            Log("Operation COMERCIAR not implemented yet");
        }
        else if(c == REDISTRIBUIR || c == REDISTRIBUIR_L)
        {
            Log("Operation REDISTRIBUIR not implemented yet");
        }
        else if(c == HACER_VIAJE || c == HACER_VIAJE_L)
        {
            Log("Operation HACER_VIAJE not implemented yet");
        }
        else if (c == "//")
        {
            cin >> c; // Skip next input
#ifdef DEBUG
            PrintCommand(c);
#endif
        }
        else
        {
            Error("Invalid input "  + c);
        }
    }
}