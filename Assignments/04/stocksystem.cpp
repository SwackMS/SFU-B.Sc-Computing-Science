// File:        stocksystem.h
// Author:      Praneet Atwal and Justin Mang
// Date:        2016-03-17
// Description: Implementation of a StockSystem class for use with CMPT 225 assignment #4
#pragma once

#include <math.h>
#include <sstream>

#include "stocksystem.h"
#include "stockitem.h"
#include "redblacktree.h"


// default constructor;
// begin with a balance of $100,000.00
StockSystem::StockSystem()
{
	balance = 100000.00;
}

// returns the balance member
double StockSystem::GetBalance()
{
	return balance;
}

// Add a new SKU to the system. Do not allow insertion of duplicate sku
bool StockSystem::StockNewItem(StockItem item)
{
	records.Insert(item);
}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found.
bool StockSystem::EditStockItemDescription(int itemsku, string desc)
{
	StockItem temp(itemsku, "", 0.00);


	//temp = new StockItem(itemsku, "", 0.00);
	
	if(!records.Search(temp))
		return false;
	else
		records.Retrieve(temp);
}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found or retailprice is negative.
bool StockSystem::EditStockItemPrice(int itemsku, double retailprice)
{

}

// Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
// Return false if balance is not sufficient to make the purchase,
//   or if SKU does not exist, or if quantity or unitprice are negative.
// Otherwise, return true and increase the item's on-hand stock by quantity,
//   and reduce balance by quantity*unitprice.
bool StockSystem::Restock(int itemsku, int quantity, double unitprice)
{

}

// Sell an item to a customer, if quantity of stock is available and SKU exists.
// Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
// If partial stock (less than quantity) available, sell the available stock and return true.
// If no stock, sku does not exist, or quantity is negative, return false.
bool StockSystem::Sell(int itemsku, int quantity)
{

}
