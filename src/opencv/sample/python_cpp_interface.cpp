#include <python3.4m/Python.h>
#include <stdio.h>
#include <string.h>

int importPythonModule (const char *binImg1_fileName)
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

    int i;

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("face");
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        /* pFunc is a new reference */
        pFunc = PyObject_GetAttrString(pModule, "get_images_from_cpp");

        if (pFunc && PyCallable_Check(pFunc))
        {
            pArgs = PyTuple_New(1);

            pValue = PyUnicode_FromStringAndSize ( binImg1_fileName, strlen(binImg1_fileName));;

            if (!pValue)
            {
               Py_DECREF(pArgs);
               Py_DECREF(pModule);
               
               fprintf(stderr, "Cannot convert argument\n");
               return 1;
            }

            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 0, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);

            Py_DECREF(pArgs);

            if (pValue != NULL)
            {
                printf("Result of call: %f\n", PyLong_AsDouble(pValue));
                Py_DECREF(pValue);
            }

            else
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }

        else
        {
            if (PyErr_Occurred())
            {
                PyErr_Print();
            }
            
            fprintf(stderr, "Cannot find function \"%s\"\n", "get_images_from_cpp");
        }
      

        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
 
   }
      
   else
   {
      PyErr_Print();
      fprintf(stderr, "Failed to load \"%s\"\n", "face");
         
      return 1;
   }

   Py_Finalize();

   return 0;
}

int importPythonModule (char *binImg1_data,
                        int   binImg1_data_len,
                        char *binImg2_data,
                        char  binImg2_data_len)
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

    int i;

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("face");
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        /* pFunc is a new reference */
        pFunc = PyObject_GetAttrString(pModule, "get_images_from_cpp");

        if (pFunc && PyCallable_Check(pFunc))
        {
            pArgs = PyTuple_New(2);

            pValue = PyBytes_FromStringAndSize ( binImg2_data, binImg1_data_len);;

            if (!pValue)
            {
               Py_DECREF(pArgs);
               Py_DECREF(pModule);
               
               fprintf(stderr, "Cannot convert argument\n");
               return 1;
            }

            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 0, pValue);

            pValue = PyBytes_FromStringAndSize ( binImg2_data, binImg2_data_len);;

            if (!pValue)
            {
               Py_DECREF(pArgs);
               Py_DECREF(pModule);
      
               fprintf(stderr, "Cannot convert argument\n");
               return 1;
            }

            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 1, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);

            Py_DECREF(pArgs);

            if (pValue != NULL)
            {
                printf("Result of call: %f\n", PyLong_AsDouble(pValue));
                Py_DECREF(pValue);
            }

            else
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }

        else
        {
            if (PyErr_Occurred())
            {
                PyErr_Print();
            }
            
            fprintf(stderr, "Cannot find function \"%s\"\n", "get_images_from_cpp");
        }
      

        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
 
   }
      
   else
   {
      PyErr_Print();
      fprintf(stderr, "Failed to load \"%s\"\n", "face");
         
      return 1;
   }

   Py_Finalize();

   return 0;
}

int maino(int argc, char *argv[])
{
   FILE *file1 = fopen (argv[1], "rb");

   if (file1 == NULL)
   {
      perror ("Error opening file1");
      return -1;
   }

   FILE *file2 = fopen (argv[2], "rb");

   if (file2 == NULL)
   {
      perror ("Error opening file2");
      return -2;
   }

   fseek (file1, 0, SEEK_END);
   fseek (file2, 0, SEEK_END);

   unsigned int img1_sz = ftell (file1);
   unsigned int img2_sz = ftell (file2);

   char img1[img1_sz + 1]; 
   img1[img1_sz + 1] = '\0';

   char img2[img2_sz + 1];
   img2[img2_sz + 1] = '\0';

   fread (img1, 1, img1_sz, file1);
   fread (img2, 1, img2_sz, file2);

   importPythonModule (img1, img1_sz, img2, img2_sz);

   return 0;
}

