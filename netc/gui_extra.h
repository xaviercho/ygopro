#ifndef _GUI_EXTRA_H_
#define _GUI_EXTRA_H_

#include <string>
#include <functional>

#include "card_data.h"
#include "sungui.h"

namespace ygopro
{

    class CommonDialog {
    public:
        virtual ~CommonDialog() {
            if(!window.expired())
                window.lock()->Destroy();
        }
    protected:
        std::weak_ptr<sgui::SGWindow> window;
    };
    
    class MessageBox {
    public:
        static void ShowOK(const std::wstring& title, const std::wstring& text, std::function<void ()> cb = nullptr);
        static void ShowOKCancel(const std::wstring& title, const std::wstring& text, std::function<void ()> cb1 = nullptr, std::function<void ()> cb2 = nullptr);
        static void ShowYesNo(const std::wstring& title, const std::wstring& text, std::function<void ()> cb1 = nullptr, std::function<void ()> cb2 = nullptr);
    };
    
    class FileDialog : public CommonDialog {
    public:
        void Show(const std::wstring& title, const std::wstring& root, const std::wstring& filter);
        void RefreshList(sgui::SGListBox* list);
        void SetOKCallback(std::function<void (const std::wstring&)> cb = nullptr) { cbOK = cb; }
        
    protected:
        std::wstring root;
        std::wstring path;
        std::wstring filter;
        std::function<void (const std::wstring&)> cbOK;
    };
    
    class FilterDialog : public CommonDialog {
    public:
        void Show();
        void SetOKCallback(std::function<void (const FilterCondition&)> cb = nullptr) { cbOK = cb; }
        void BeginSearch();
        std::pair<int, int> ParseValue(const std::wstring& valstr);
        
    protected:
        std::function<void (const FilterCondition&)> cbOK;
        std::weak_ptr<sgui::SGTextEdit> keyword;
        std::weak_ptr<sgui::SGComboBox> type1;
        std::weak_ptr<sgui::SGComboBox> type2;
        std::weak_ptr<sgui::SGComboBox> type3;
        std::weak_ptr<sgui::SGComboBox> attribute;
        std::weak_ptr<sgui::SGComboBox> race;
        std::weak_ptr<sgui::SGTextEdit> attack;
        std::weak_ptr<sgui::SGTextEdit> defence;
        std::weak_ptr<sgui::SGTextEdit> star;
    };
    
}

#endif
