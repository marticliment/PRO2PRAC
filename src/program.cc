#include <iostream>
#include "Valley.hh"
#include "debug.hh"
#include "ProductReference.hh"
#include "NavigationDecisions.hh"

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


const string ERR_NE_CITY = "error: no existe la ciudad";
const string ERR_RE_CITY = "error: ciudad repetida";
const string ERR_NE_PROD = "error: no existe el producto";
const string ERR_NE_PROD_CITY = "error: la ciudad no tiene el producto";
const string ERR_AE_PROD = "error: la ciudad ya tiene el producto";

#ifdef DEBUG
const string green("\033[1;32m");
const string reset("\033[0m");
#endif

void PrintCommand(string command)
{
#ifdef DEBUG
    cout << green << "#" + command << reset << endl;
#else
    cout << "#" + command << endl;
#endif
}


/// @brief Entry point of the program
int main()
{
    Valley::InitializeFromStream(cin);
    string command;
    while(cin >> command && command != FIN)
    {   
        //  Se leerán los identificadores de las ciudades indicando la estructura
        // de la cuenca. No se escribe nada. Los inventarios de las ciudades quedan vacíos. El
        // barco conserva sus atributos de productos pero no ha realizado viajes en la nueva
        // cuenca.
        if(command == LEER_RIO || command == LEER_RIO_L)
        {
            PrintCommand(command);
            Valley::ReadCitiesFromStream(cin);
        }

        // Se leerá el identificador de una ciudad. Si la ciudad no existe
        // se escribirá un mensaje de error. Si la ciudad existe, se leerá un número que indica la cantidad 
        // de elementos del inventario y para cada uno de ellos se leerá el
        // identificador del producto, cuantas unidades tiene la ciudad y cuantas necesita. El
        // número de unidades necesitadas siempre ha de ser mayor que 0. Aunque la ciudad no exista, 
        // habrá datos de su inventario que igualmente se han de leer aunque
        // no se usen, para pasar a la siguiente operación.
        else if(command == LEER_INVENTARIO || command == LEER_INVENTARIO_L)
        {
            string city_id;
            cin >> city_id;
            PrintCommand(command + " " + city_id);

            if(!Valley::HasCity(city_id))
                cout << ERR_NE_CITY << endl;

            // Even if the city is invalid we need to read the provided values through cin
            // Therefore we will read to the default invalid city
            Valley::GetCity(city_id).ReadFromStream(cin);
        }
        
        // Se leerán los inventarios de ciudades del río. Todas las ciudades existirán. Los datos del inventario 
        // son como en la funcionalidad anterior.
        // No necesariamente todas las ciudades del río tendrán inventario.
        else if(command == LEER_INVENTARIOS || command == LEER_INVENTARIOS_L)
        {
            PrintCommand(command);
            string city_id;
            while(cin >> city_id && city_id != "#")
                Valley::GetCity(city_id).ReadFromStream(cin);
        }
        
        // Se leerá el identificador del producto que se quiere comprar
        // y la cantidad, y el identificador del producto que se quiere vender y la cantidad.
        // Si algún producto no existe, se escribirá un mensaje de error. Si los dos productos
        // son el mismo, se escribirá un mensaje de error. Se garantiza que ambas cantidades
        // serán no negativas y al menos una de ellas será estrictamente positiva.
        else if(command == MODIFICAR_BARCO || command == MODIFICAR_BARCO_L)
        {
            PrintCommand(command);
            Valley::GetShip().ReadFromStream(cin);
        }
        
        // Se escriben los cuatro valores mencionados en la anterior operación y los viajes realizados en la cuenca 
        // actual, en orden cronológico. Para cada
        // viaje solo se ha de escribir la última ciudad visitada de la ruta escogida.
        else if(command == ESCRIBIR_BARCO || command == ESCRIBIR_BARCO_L)
        {
            PrintCommand(command);
            auto& ship = Valley::GetShip();
            Product& buying = ship.BuyingProduct();
            Product& selling = ship.SellingProduct();
            cout << buying.GetId() << ' ' << buying.MissingAmount() << ' ';
            cout << selling.GetId() << ' ' << selling.GetCurrentAmount() << endl;
            if(ship.GetLastVisitedCity() != "")
                cout << ship.GetLastVisitedCity() << endl;
        }
        
        // Escribe cuantos productos diferentes hay.
        else if(command == CONSULTAR_NUM || command == CONSULTAR_NUM_L)
        {
            PrintCommand(command);
            cout << ProductReference::Count() << endl;
        }
        
        // Se lee el número de productos nuevos, mayor que 0. Sus
        // identificadores serán correlativos a partir del último producto existente. Se leerán
        // sus pesos y volúmenes respectivos
        else if(command == AGREGAR_PRODUCTOS || command == AGREGAR_PRODUCTOS_L)
        {
            int count;
            cin >> count;
            PrintCommand(command + " " + to_string(count));
            ProductReference::AddFromStream(cin, count);
        }
        
        // se escribirá un mensaje de error. Si la ciudad existe, se escribirá su inventario, y el
        // peso y el volumen total de los productos almacenados.
        // Se leerá el identificador de una ciudad. Si la ciudad no existe
        else if(command == ESCRIBIR_CIUDAD || command == ESCRIBIR_CIUDAD_L)
        {
            string city_id;
            cin >> city_id;
            PrintCommand(command + " " + city_id);

            if(Valley::HasCity(city_id))
            {
                auto& city = Valley::GetCity(city_id);
                for(int i: city.GetProductIds())
                {
                    auto& product = city.GetProduct(i);
                    cout << product.GetId() << ' ' << product.GetCurrentAmount() << ' ' << product.GetWantedAmount() << endl;
                }
                cout << city.GetWeight() << ' ' << city.GetVolume() << endl;
            }
            else
                cout << ERR_NE_CITY << endl;
        }

        // Se lee el identificador de un producto. Si no existe el producto se escribe 
        // un mensaje de error. En caso contrario se escribe el peso y volumen
        // del producto.
        else if(command == ESCRIBIR_PRODUCTO || command == ESCRIBIR_PRODUCTO_L)
        {
            int product_id;
            cin >> product_id;
            PrintCommand(command + " " + to_string(product_id));
            if(ProductReference::Contains(product_id))
            {
                auto& product = ProductReference::Get(product_id);
                cout << product_id << ' ' << product.GetWeight() << ' ' << product.GetVolume() << endl;
            }
            else
                cout << ERR_NE_PROD << endl;
        }
        
        // Se leerá el identificador de una ciudad, de un producto y las
        // unidades que tiene y que quiere. Si el producto no existe escribe un mensaje de
        // error. Si la ciudad no existe, escribe un mensaje de error. Si el producto ya está en
        // el inventario de la ciudad, escribe un mensaje de error. Si no hay errores, los datos
        // de ese producto se añaden a la ciudad, modificándose el peso y el volumen total si
        // hace falta. Se escribe el peso y el volumen total. El número de unidades necesitadas
        // siempre ha de ser mayor que 0.
        else if(command == PONER_PROD || command == PONER_PROD_L)
        {
            string city_id;
            int product_id, current, wanted;
            cin >> city_id >> product_id >> current >> wanted;
            PrintCommand(command + " " + city_id + " " + to_string(product_id));

            if (!ProductReference::Contains(product_id))
                cout << ERR_NE_PROD << endl;
            else if(!Valley::HasCity(city_id))
                cout << ERR_NE_CITY << endl;
            else
            {
                auto& city = Valley::GetCity(city_id);
                if (city.HasProduct(product_id))
                    cout << ERR_AE_PROD << endl;
                else
                {
                    city.AddProduct(Product(product_id, current, wanted));
                    cout << city.GetWeight() << ' ' << city.GetVolume() << endl;
                }
            }
        }
        
        //  Se leerá el identificador de una ciudad, de un producto y las
        // unidades que tienen y que quiere. Si el producto no existe escribe un mensaje de
        // error. Si la ciudad no existe, escribe un mensaje de error. Si el producto no está en
        // el inventario de la ciudad, escribe un mensaje de error. Si no hay errores, los datos
        // de ese producto sustituyen a los que había en la ciudad, modificándose el peso y
        // el volumen total si hace falta. Se escribe el peso y el volumen total. El número de
        // unidades necesitadas se puede modificar, pero siempre ha de ser mayor que 0.
        else if(command == MODIFICAR_PROD || command == MODIFICAR_PROD_L)
        {
            string city_id;
            int product_id, current, wanted;
            cin >> city_id >> product_id >> current >> wanted;
            PrintCommand(command + " " + city_id + " " + to_string(product_id));
            
            if (!ProductReference::Contains(product_id))
                cout << ERR_NE_PROD << endl;
            else if(!Valley::HasCity(city_id))
                cout << ERR_NE_CITY << endl;
            else 
            {
                auto& city = Valley::GetCity(city_id);
                if(!city.HasProduct(product_id))
                    cout << ERR_NE_PROD_CITY << endl;
                else
                {
                    city.UpdateProduct(Product(product_id, current, wanted));
                    cout << city.GetWeight() << ' ' << city.GetVolume() << endl;
                }
            }
        }

        // Se leerá el identificador de una ciudad y de un producto. Si
        // el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe
        // un mensaje de error. Si el producto no está en el inventario de la ciudad, escribe
        // un mensaje de error. Si no hay errores, se quitan los datos de este producto en la
        // ciudad, modificándose el peso y el volumen total si hace falta. Se escribe el peso y
        // el volumen total.
        else if(command == QUITAR_PROD || command == QUITAR_PROD_L)
        {
            string city_id;
            int product_id;
            cin >> city_id >> product_id;
            PrintCommand(command + " " + city_id + " " + to_string(product_id));

            if (!ProductReference::Contains(product_id))
                cout << ERR_NE_PROD << endl;
            else if(!Valley::HasCity(city_id))
                cout << ERR_NE_CITY << endl;
            else 
            {
                auto& city = Valley::GetCity(city_id);
                if(!city.HasProduct(product_id))
                    cout << ERR_NE_PROD_CITY << endl;
                else
                {
                    city.RemoveProduct(product_id);
                    cout << city.GetWeight() << ' ' << city.GetVolume() << endl;
                }
            }
        }
        
        // Se leerá el identificador de una ciudad y de un producto. Si
        // el producto no existe escribe un mensaje de error. Si la ciudad no existe, escribe un
        // mensaje de error. Si el producto no está en el inventario de la ciudad, escribe un
        // mensaje de error. Si no hay errores, se escribe cuantas unidades de ese producto
        // tiene y quiere la ciudad.
        else if(command == CONSULTAR_PROD || command == CONSULTAR_PROD_L)
        {
            string city_id;
            int product_id;
            cin >> city_id >> product_id;
            PrintCommand(command + " " + city_id + " " + to_string(product_id));

            if (!ProductReference::Contains(product_id))
                cout << ERR_NE_PROD << endl;
            else if(!Valley::HasCity(city_id))
                cout << ERR_NE_CITY << endl;
            else 
            {
                auto& city = Valley::GetCity(city_id);
                if(!city.HasProduct(product_id))
                    cout << ERR_NE_PROD_CITY << endl;
                else
                {
                    auto& product = city.GetProduct(product_id);
                    cout << product.GetCurrentAmount() << ' ' << product.GetWantedAmount() << endl;                    
                }
            }        
        }
        
        //  Se leerán los identificadores de dos ciudades. Si no existe alguna
        // de las dos (o las dos), se escribe un mensaje de error. Si las ciudades existen y son
        // la misma, se escribe un mensaje de error. Si las ciudades existen y son diferentes,
        // comercian entre ellas.
        else if(command == COMERCIAR || command == COMERCIAR_L)
        {
            string city1_id, city2_id;
            cin >> city1_id >> city2_id;
            PrintCommand(command + " " + city1_id + " " + city2_id);

            if(!Valley::HasCity(city1_id) || !Valley::HasCity(city2_id))
                cout << ERR_NE_CITY << endl;
            else if (city1_id == city2_id)
                cout << ERR_RE_CITY << endl;
            else
            {
                auto& city1 = Valley::GetCity(city1_id);
                auto& city2 = Valley::GetCity(city2_id);
                city1.TradeWith(city2);
            }
        }
        
        // No se leen datos. La ciudad de la desembocadura comercia con su
        // ciudad río arriba a mano derecha y luego con la ciudad río arriba a mano izquierda,
        // y así sucesivamente.
        else if(command == REDISTRIBUIR || command == REDISTRIBUIR_L)
        {
            PrintCommand(command);
            Valley::DoTrades();
        }
        
        // No se leen datos. El barco busca la ruta a partir de la desembocadura que le permita
        // comprar y vender el mayor número posible de productos.
        // En caso que haya más de una ruta que lo cumpla, se queda con la más corta, y en
        // caso de que tengan la misma longitud, se queda con la que viene río arriba a mano
        // derecha. Una vez encontrada la ruta, se hace el viaje y se compran y venden los
        // productos a lo largo de la ruta, modificándose los inventarios de las ciudades. Se
        // escribe el total de unidades de productos compradas y vendidas por el barco.
        else if(command == HACER_VIAJE || command == HACER_VIAJE_L)
        {
            PrintCommand(command);
            auto route = Valley::GetBestRoute();
            cout << Valley::NavigateRoute(route) << endl;
        }
        
        // Comment line
        else if (command == "//")
        {
            getline(cin, command); // Skip current line            
        }
        else
        {
            Error("Invalid input "  + command);
        }
    }
}