# **Management System - Dental Clinic**
Development of a system in C Language for the management of the dental clinic "Char of Smiles", including the manipulation of equipment stock, consultations and patients.

## **Developers**
> [Letícia Vieira Gonçalves - Git Master](https://github.com/LeticiaVieirg)
>
> [Maria Isabelly de Lima Sousa - Edit](https://github.com/isabellylimals)
> 
> [Allan Gabriel Silva de Freitas - Encoder](https://github.com/Allan-Gabriell)
> 
> [Levitico Rimon Perez Andrade Alves - Testator](https://github.com/LEVEL303)
***

# **Table of Contents**
> [Introduction](#introduction)
> 
> [Problematic](#problematic)
> 
> [Goal](#goal)
>
> [Development](#development)
>
> [Build and rum](#build-and-run)
>

***


## **Introduction**
The efficient management of a dental clinic is crucial to ensure its smooth operation and maximum effectiveness in patient care. This ranges from the organization of medical records to the scheduling of appointments and the administration of available resources. In order to simplify all the operations necessary for the operation of the business.

This system uses data structures such as linked lists to organize patient information, offices, treatment histories, and other aspects relevant to the clinic.

## **Problematic**
The management system for a dental clinic - CHAR OF SMILLE, developed in C Language, aims to simplify the operations crucial to the efficient functioning of the establishment. It provides features such as adding, deleting, searching and editing patients and appointments, as well as listing patients and their appointment histories. These features are essential to ensure effective and organized management of dental clinic activities.

## **Goal**
The use of different data structures in the project brought significant improvements in several areas. The Binary Search Tree (BTR) was efficient in organizing patients by CPF, providing speed in searches and automatic display of ordered data, in addition to facilitating insertion and editing without compromising the structure. The hash table, in turn, optimized the management of products by barcode, allowing quick access and simplifying inventory management. The use of a heap in query management dynamically prioritized the most urgent ones, ensuring fast and efficient responses even with high demand.

## **Development**

### Attributes
#### *Atributes*
- [x] Identification
- [x] Type
- [x] Available Equipment - Stock
- [x] Patient

#### *Patients Attributts*
- [x] Name
- [x] Age
- [x] CPF

#### *Menu*
- [x] Added
- [x] Delete 
- [x] Search 
- [x] Print 
- [x] Exit
***


## **Build and Run**
    gcc src/main.c src/functions.c src/patient.c src/stock.c src/consultation.c -o teste1
