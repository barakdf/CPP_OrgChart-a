//
// Created by barak on 18/05/2022.
//

#include "doctest.h"
#include "sources/OrgChart.hpp"
//#include "sources/OrgChart.cpp"

/** Exceptions :
 *      add_sub -> if the parent param does not exist - throw
 *
 *  Special Cases:
 *      add_root -> if there is already a defined root, it will be replaced with the new one.
 *      add_sub -> if the parent exist twice, the new sub will be sub of one of them (not include in test)
 *
 *      */

TEST_CASE ("Valid Cases") {

            SUBCASE("University OrgChart") {
        /** ~~~ Bicol University ~~~
         *
         *      {BOARD OF REGENTS}
         *              |
         *      [University President]
         * -----|-------------------------------------|----------------------------|-----------------------|-----------
         * [C&P RelationOffice]                       |            [I&C TechOffice] [Presidential Management Staff]
         * --------------------------[Office of the VP ADMIN and Finance]----------------------------------------------
         *               |----------------------------------------------------|
         *      [Administrative Services Division]                    [Financial Services Division]
         * */

        ariel::OrgChart bicol_UV;
        /* add direct root and the first and only sub of the root */
        CHECK_NOTHROW(bicol_UV.add_root("BOARD OF REGENTS").add_sub("BOARD OF REGENTS", "University President"));
        /* add level two of the hierarchy */
        CHECK_NOTHROW(bicol_UV.add_sub("University President", "C&P RelationOffice")
                              .add_sub("University President", "Office of the VP ADMIN and Finance")
                              .add_sub("University President", "I&C TechOffice")
                              .add_sub("University President", "Presidential Management Staff"));
        /* add level three subs of "Office of the VP ADMIN and Finance" */
        CHECK_NOTHROW(bicol_UV.add_sub("Office of the VP ADMIN and Finance", "Administrative Services Division")
                              .add_sub("Office of the VP ADMIN and Finance", "Financial Services Division"));

        std::vector<std::string> level_order_LIST;
        std::vector<std::string> reverse_level_order_LIST;
                SUBCASE("Level Order and reverse relation check") {
            for (auto it = bicol_UV.begin_level_order(); it != bicol_UV.end_level_order(); ++it) {
                level_order_LIST.push_back(*it);
            }
//            /* THIS is an example of result list in level order iteration */
            std::vector<std::string> level_order_TEST_RESULT =
                    {"BOARD OF REGENTS", "University President", "C&P RelationOffice",
                     "Office of the VP ADMIN and Finance", "I&C TechOffice", "Presidential Management Staff",
                     "Administrative Services Division", "Financial Services Division"
                    };
//
//            /* in this for we check if each step of the iterator is correct based on the test result list*/
            size_t index = 0;

            for (auto it = bicol_UV.begin_level_order(); it != bicol_UV.end_level_order(); ++it) {

                        CHECK_EQ((*it), level_order_TEST_RESULT[index]);
                index++;
            }
            /* in this for we fill a reverse level order from the level order list. (starting from end of list)*/
            if (level_order_LIST.size() > 1) {
                for (size_t i = level_order_LIST.size() - 1; i >= 0; --i) {

                            CHECK_NOTHROW(reverse_level_order_LIST.push_back(level_order_LIST[i]));
                }
            }


            /* check for the reverse order list with his actual Iterator */
            index = 0;
            for (auto it = bicol_UV.begin_reverse_order(); it != bicol_UV.end_reverse_order(); ++it) {

                        CHECK_EQ((*it), reverse_level_order_LIST[index]);
                index++;
            }

            /* check on ForEach loop, should behave like level-order Iterator*/
            index = 0;
            for (auto element: bicol_UV) {

                        CHECK_EQ(element, level_order_TEST_RESULT[index]);
                index++;
            }
        }

                SUBCASE("PreOrder") {
            /* THIS is an example of result list in pre-order iteration */
            std::vector<std::string> pre_order_LIST_TEST_RESULT = {
                    "BOARD OF REGENTS",
                    "University President",
                    "C&P RelationOffice",
                    "Office of the VP ADMIN and Finance", "Administrative Services Division",
                    "Financial Services Division", "I&C TechOffice",
                    "Presidential Management Staff"
            };
            size_t index = 0;
            /* in this for we check if each step of the iterator is correct based on the test result list*/
            for (auto it = bicol_UV.begin_preorder(); it != bicol_UV.end_preorder(); ++it) {
                        CHECK_EQ((*it), pre_order_LIST_TEST_RESULT[index]);
                index++;
            }
        }
    }

            SUBCASE("Saiyans Race Tree") {
        /**                {Akumo} ----> King of all saiyans (referred here as the ancestor)
         *                     |
         *          |-----------------------------|
         *      [King Vegeta]                [Bardock]
         *           |                           |
         *       |-------|                  |--------|
         *  [Tarble]  [Vegeta]            [Goku]   [Raditz]
         *               |                  |
         *          |---------|         |--------|
         *      [Trunks] [Bulla]     [Gohan]   [Goten]
         *                              |
         *                           [Pan]
         * */

        ariel::OrgChart saiyans;

        /* Insertion of the saiyan race */
        saiyans.add_root("Akumo").
                add_sub("Akumo", "King Vegeta").add_sub("Akumo", "Bardock");
        /* king Vegeta children */
        saiyans.add_sub("King Vegeta", "Tarble").add_sub("King Vegeta", "Vegeta");
        /* Bardock children */
        saiyans.add_sub("Bardock", "Goku").add_sub("Bardock", "Raditz");
        /* Vegeta children */
        saiyans.add_sub("Vegeta", "Trunks").add_sub("Vegeta", "Bulla");
        /* Goku children */
        saiyans.add_sub("Goku", "Gohan").add_sub("Goku", "Goten");
        /* Gohan Daughter */
        saiyans.add_sub("Gohan", "Pan");


        auto level_order_iter = saiyans.begin_level_order();
        auto pre_order_iter = saiyans.begin_preorder();


        /* the root should be the same in the beginning of both iterators*/
                SUBCASE("Root is equal in pre-order and level-order") {

//                    std::cout << (*pre_order_iter)<< std::endl;
                    CHECK_EQ((*pre_order_iter), "Akumo");
                    CHECK_EQ((*level_order_iter), (*pre_order_iter));
        }


        level_order_iter++;
        pre_order_iter++;


                SUBCASE("second value is equal in pre-order and level-order") {
                    CHECK_EQ((*level_order_iter), "King Vegeta");

                    CHECK_EQ((*level_order_iter), (*pre_order_iter));
        }

        level_order_iter++;
        pre_order_iter++;

        SUBCASE("Third value is not equal in pre-order and level order (in this case)") {
                    CHECK_EQ((*level_order_iter), "Bardock");
                    CHECK_EQ((*pre_order_iter), "Tarble");
                    CHECK_NE((*level_order_iter), (*pre_order_iter));
                }


        auto reverse_level_order_iter = saiyans.begin_reverse_order();

                SUBCASE("Begin of reverse-level-order should be Pan (Gohan's Daughter)") {
                    CHECK_EQ((*reverse_level_order_iter), "Pan");
        }


        std::vector<std::string> level_order_saiyans = {
                "Akumo",
                "King Vegeta", "Bardock",
                "Tarble", "Vegeta", "Goku", "Raditz",
                "Trunks", "Bulla", "Gohan", "Goten",
                "Pan"
        };

                SUBCASE("level-order list") {

            size_t index = 0;
            for (auto saiyan: saiyans) {

                        CHECK_EQ(saiyan, level_order_saiyans[index]);

            }
        }

        std::vector<std::string> reverse_level_order_saiyans;
        for (size_t i = level_order_saiyans.size() - 1; i >= 0; --i) {
            reverse_level_order_saiyans.push_back(level_order_saiyans[i]);
        }

                SUBCASE("reverse-level-order list") {
            size_t index = 0;
            for (auto it = saiyans.begin_reverse_order(); it != saiyans.end_reverse_order() ; ++it) {

                CHECK_EQ(reverse_level_order_saiyans[index], (*it));
            }
        }
                SUBCASE("pre-order list") {
            std::vector<std::string> pre_order_saiyans = {
                    "Akumo",
                    "King Vegeta", "Tarble","Vegeta",
                    "Trunks","Bulla",
                    "Bardock", "Goku",
                    "Gohan", "Pan",
                    "Goten",
                    "Raditz"
            };
            size_t index = 0;
            for (auto it = saiyans.begin_preorder(); it != saiyans.end_preorder() ; ++it) {

                        CHECK_EQ(pre_order_saiyans[index], (*it));
            }

        }
    }
}

TEST_CASE ("Exceptions") {
    ariel::OrgChart test;
    /* try to add sub when root does not exist */
    CHECK_THROWS(test.add_sub("Not_exist", "Fail"));
    /* adding root but still adding sub to a node that dont exist */
    test.add_root("ROOT");
    CHECK_THROWS(test.add_sub("Dont_exist", "Fail"));
    /* adding sub to the root -> should succeed */
    CHECK_NOTHROW(test.add_sub("ROOT", "exist"));
    /* even if the root has childs we cant add subs to non-existing parent*/
    CHECK_THROWS(test.add_sub("dont_exist","Fail"));
    /* adding sub when there is already a node with the same name in the chart -> should succeed */
    CHECK_NOTHROW(test.add_sub("ROOT", "exist"));

    SUBCASE("Special Cases") {
        /* when we add root where there is an already existing root -> should succeed AND replace the current root */
        CHECK_NOTHROW(test.add_root("ROOT2"));
        auto it = test.begin_preorder();
        CHECK_EQ((*it), "ROT2");
    }

}