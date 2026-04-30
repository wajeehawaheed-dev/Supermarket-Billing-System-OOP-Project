#include "ProductsForm.h"
#include "AddProductForm.h"
#include "EditProductForm.h"
#include "SearchProductForm.h"

namespace OOP_PROJECT_SEMESTER2 {

    void ProductsForm::btnAdd_Click(Object^ sender, EventArgs^ e) {
        AddProductForm^ form = gcnew AddProductForm();
        form->ShowDialog();
        loadGrid();
    }

    void ProductsForm::btnEdit_Click(Object^ sender, EventArgs^ e) {
        int id = getSelectedID();
        if (id == -1) {
            MessageBox::Show("Please select a product to edit.", "No Selection",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        EditProductForm^ form = gcnew EditProductForm(id);
        form->ShowDialog();
        loadGrid();
    }

    void ProductsForm::btnDelete_Click(Object^ sender, EventArgs^ e) {
        int id = getSelectedID();
        if (id == -1) {
            MessageBox::Show("Please select a product to delete.", "No Selection",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        if (MessageBox::Show("Are you sure you want to delete this product?", "Confirm Delete",
            MessageBoxButtons::YesNo, MessageBoxIcon::Warning)
            == System::Windows::Forms::DialogResult::Yes) {
            pm->deleteFromDB(id);
            loadGrid();
        }
    }

    void ProductsForm::btnSearch_Click(Object^ sender, EventArgs^ e) {
        SearchProductForm^ form = gcnew SearchProductForm();
        form->ShowDialog();
    }

    void ProductsForm::btnRefresh_Click(Object^ sender, EventArgs^ e) {
        loadGrid();
    }
}