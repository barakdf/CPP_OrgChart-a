//
// Created by barak on 16/05/2022.
//

#ifndef CPP_ORGCHART_A_ORGCHART_HPP
#define CPP_ORGCHART_A_ORGCHART_HPP

#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <unordered_map>

namespace ariel {
    class OrgChart {

    public:
        class Node {
        private:
            std::string title;
            Node* parent;
            std::vector<Node*> childs;
            int _size;
            size_t index;

        public:
            Node(std::string  title, size_t _index):title(std::move(title)), parent(nullptr), _size(0), index(_index){}

            void add_child(Node* child);

            void set_title(std::string _title);

            size_t get_num_childs();

            int size();

            friend std::ostream & operator<< (std::ostream &ostream, Node& node);
        };

    private:
        Node *root;

    public:


        std::unordered_map<std::string, Node> members;
        OrgChart() : root(nullptr) {}

        OrgChart &add_root(const std::string& title);

        OrgChart &add_sub(const std::string& curr_title, const std::string& new_title);

        auto get_members();




        /** -------------- Iterator Classes */

        /* LEVEL ORDER CLASS */
        class LevelOrder {
        private:
            Node *pointer_to_current_node;
        public:
            explicit LevelOrder(Node *ptr = nullptr)
                    : pointer_to_current_node(ptr) {}

            LevelOrder &operator=(const LevelOrder &);
            Node & operator*() const;
            Node * operator&() const;
            Node * operator->() const;

            LevelOrder& operator++();
            const LevelOrder operator++(int );

            bool operator==(const LevelOrder& other);
            bool operator!=(const LevelOrder& other);


        };


        /* REVERSE LEVEL ORDER CLASS */
        class ReverseLevelOrder {
        private:
            Node *pointer_to_current_node;

        public:
            explicit ReverseLevelOrder(Node *ptr = nullptr)
                    : pointer_to_current_node(ptr) {}

            ReverseLevelOrder &operator=(ReverseLevelOrder &);
            Node & operator*() const;
            Node * operator&() const;
            Node * operator->() const;

            ReverseLevelOrder& operator++();
            const ReverseLevelOrder operator++(int );

            bool operator==(const ReverseLevelOrder& other);
            bool operator!=(const ReverseLevelOrder& other);

        };

        /* PRE ORDER CLASS */
        class PreOrder {
        private:
            Node *pointer_to_current_node;

        public:
            explicit PreOrder(Node *ptr = nullptr)
                    : pointer_to_current_node(ptr) {}

            PreOrder &operator=(Node &);
            Node & operator*() const;
            Node * operator&() const;
            Node * operator->() const;

            PreOrder& operator++();
            const PreOrder operator++(int );

            bool operator==(const PreOrder& other);
            bool operator!=(const PreOrder& other);

        };
        /** Iterator Methods */

        /* LEVEL ORDER */
        LevelOrder begin_level_order();

        LevelOrder end_level_order();

        LevelOrder begin();
        LevelOrder end();

        /* REVERSE LEVEL ORDER */
        ReverseLevelOrder begin_reverse_order();

        ReverseLevelOrder end_reverse_order();

        /* PRE ORDER */
        PreOrder begin_preorder();

        PreOrder end_preorder();


        friend std::ostream & operator<< (std::ostream &ostream, OrgChart& orgChart);

    };
}


#endif //CPP_ORGCHART_A_ORGCHART_HPP
